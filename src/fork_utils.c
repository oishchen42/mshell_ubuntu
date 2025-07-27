/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:42:03 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/21 19:50:31 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	is_state_builtin(t_command cmd)
{
	if (!cmd.args)
		return (FAIL);
	if (ft_strncmp(cmd.args[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd.args[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd.args[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd.args[0], "exit", 5) == 0)
		return (1);
	return (0);
}

int	run_pipex(t_mshell_data *mshell_struct)
{
	int		pipes[2][2];
	pid_t	*pids;
	int		i;

	if (!mshell_struct->pipex->n_cmds)
		return (EXIT_SUCCESS);
	pids = malloc(sizeof(pid_t) * (mshell_struct->pipex->n_cmds));
	i = 0;
	while (i < mshell_struct->pipex->n_cmds)
	{
		if (pipe(pipes[1]) == -1)
			return (EPIPE);
		if (is_state_builtin(mshell_struct->pipex->commands[i])) // some cmds like export, cd, exit should not be run in fork!!!
		{
			parse_builtin(mshell_struct->pipex->commands[i], mshell_struct);
			pids[i] = -1;
		}
		else
		{
			pids[i] = fork();
			if (pids[i] < 0)
				return (ECHILD);
			if (pids[i] == 0)
				run_fork(i, mshell_struct, pipes);
		}
		if (i != 0)
			close_pipe(pipes[0]);
		pipes[0][READ_END] = pipes[1][READ_END];
		pipes[0][WRITE_END] = pipes[1][WRITE_END];
		i++;
	}
	close_pipe(pipes[0]);
	close_pipe(pipes[1]);
	return (wait_for_child_procs(pids, mshell_struct->pipex->n_cmds));
}

void	run_fork(int i, t_mshell_data *mshell_struct, int pipes[2][2])
{
	int	curr_fd[2];

	if (mshell_struct->pipex->n_cmds == 1)
		pipes[1][WRITE_END] = -1;
	if (i == 0)
		run_first_cmd(mshell_struct, pipes[1]);
	else if (i < (mshell_struct->pipex->n_cmds - 1))
	{
		close(pipes[0][WRITE_END]);
		close(pipes[1][READ_END]);
		curr_fd[READ_END] = pipes[0][READ_END];
		curr_fd[WRITE_END] = pipes[1][WRITE_END];
		run_cmd(mshell_struct->pipex->commands[i], mshell_struct, curr_fd);
	}
	else
		run_last_cmd(mshell_struct, pipes[0]);
}

void	run_first_cmd(t_mshell_data *mshell_struct, int pipe[2])
{
	close(pipe[READ_END]);
	if (mshell_struct->pipex->infile)
	{
		pipe[READ_END] = open(mshell_struct->pipex->infile, O_RDONLY);
		if (pipe[READ_END] < 0)
			exit_with_error(strerror(errno), mshell_struct->pipex->infile, errno);
	}
	else
		pipe[READ_END] = -1;
	run_cmd(mshell_struct->pipex->commands[0], mshell_struct, pipe);
}

void	run_last_cmd(t_mshell_data *mshell_struct, int pipe[2])
{
	int	flags;

	close(pipe[WRITE_END]);
	if (mshell_struct->pipex->outfile)
	{
		if (access(mshell_struct->pipex->outfile, F_OK) == 0
			&& access(mshell_struct->pipex->outfile, W_OK) == -1)
			exit_with_error(strerror(errno), mshell_struct->pipex->outfile, 1);
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		if (mshell_struct->pipex->is_heredoc)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		pipe[WRITE_END] = open(mshell_struct->pipex->outfile, flags, 0644);
		if (pipe[WRITE_END] < 0)
			exit_with_error(strerror(errno), mshell_struct->pipex->outfile, errno);
	}
	else
		pipe[WRITE_END] = -1;
	run_cmd(mshell_struct->pipex->commands[mshell_struct->pipex->n_cmds - 1], mshell_struct,
		pipe);
}

void	run_cmd(t_command command, t_mshell_data *mshell_struct, int fd[])
{
	char	*cmd;
	int		err_code;
	int		builtin_status;

	if (fd[READ_END] != -1)
	{
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
	}
	if (fd[WRITE_END] != -1)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
	}
	builtin_status = parse_builtin(command, mshell_struct);
	if (builtin_status != CMD_NOT_FOUND)
		exit(builtin_status);
	cmd = get_exec_cmd(command.args[0], mshell_struct->env, &err_code);
	if (cmd && (access(cmd, F_OK) == 0) && (access(cmd, X_OK) == -1))
	{
		free(cmd);
		exit_with_error_and_free("permission denied", NULL, 126);
	}
	if (cmd == NULL && err_code == ERROR_NO_FILE)
		exit_with_error_and_free(strerror(errno), NULL, 127);
	if (cmd == NULL)
		exit_with_error_and_free("command not found", NULL, 127);
	execve(cmd, command.args, mshell_struct->env);
	free(cmd);
	exit_with_error("execve error", NULL, 127);
}
