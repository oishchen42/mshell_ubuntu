/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:42:03 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/14 00:14:41 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	run_pipex(t_pipex *pipex_struct)
{
	int		pipes[2][2];
	pid_t	*pids;
	int		i;

	if (!pipex_struct->n_cmds)
		return (EXIT_SUCCESS);
	pids = malloc(sizeof(pid_t) * (pipex_struct->n_cmds));
	i = 0;
	while (i < pipex_struct->n_cmds)
	{
		if (pipe(pipes[1]) == -1)
			return (EPIPE);
		pids[i] = fork();
		if (pids[i] < 0)
			return (ECHILD);
		if (pids[i] == 0)
			run_fork(i, pipex_struct, pipes);
		if (i != 0)
			close_pipe(pipes[0]);
		pipes[0][READ_END] = pipes[1][READ_END];
		pipes[0][WRITE_END] = pipes[1][WRITE_END];
		i++;
	}
	close_pipe(pipes[0]);
	close_pipe(pipes[1]);
	return (wait_for_child_procs(pids, pipex_struct->n_cmds));
}

void	run_fork(int i, t_pipex *pipex_struct, int pipes[2][2])
{
	int	curr_fd[2];

	if (pipex_struct->n_cmds == 1)
		pipes[1][WRITE_END] = -1;
	if (i == 0)
		run_first_cmd(pipex_struct, pipes[1]);
	else if (i < (pipex_struct->n_cmds - 1))
	{
		close(pipes[0][WRITE_END]);
		close(pipes[1][READ_END]);
		curr_fd[READ_END] = pipes[0][READ_END];
		curr_fd[WRITE_END] = pipes[1][WRITE_END];
		run_cmd(pipex_struct->cmds[i], pipex_struct->envp, curr_fd);
	}
	else
		run_last_cmd(pipex_struct, pipes[0]);
}

void	run_first_cmd(t_pipex *pipex_struct, int pipe[2])
{
	close(pipe[READ_END]);
	if (pipex_struct->infile)
	{
		pipe[READ_END] = open(pipex_struct->infile, O_RDONLY);
		if (pipe[READ_END] < 0)
			exit_with_error(strerror(errno), pipex_struct->infile, errno);
	}
	else
		pipe[READ_END] = -1;
	run_cmd(pipex_struct->cmds[0], pipex_struct->envp, pipe);
}

void	run_last_cmd(t_pipex *pipex_struct, int pipe[2])
{
	int	flags;

	close(pipe[WRITE_END]);
	if (pipex_struct->outfile)
	{
		if (access(pipex_struct->outfile, F_OK) == 0
			&& access(pipex_struct->outfile, W_OK) == -1)
			exit_with_error(strerror(errno), pipex_struct->outfile, 1);
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		if (pipex_struct->is_heredoc)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		pipe[WRITE_END] = open(pipex_struct->outfile, flags, 0644);
		if (pipe[WRITE_END] < 0)
			exit_with_error(strerror(errno), pipex_struct->outfile, errno);
	}
	else
		pipe[WRITE_END] = -1;
	run_cmd(pipex_struct->cmds[pipex_struct->n_cmds - 1], pipex_struct->envp,
		pipe);
}

void	run_cmd(char *argv, char *envp[], int fd[])
{
	char	*cmd;
	char	**args;
	int		err_code;

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
	args = ft_split_cmd(argv, ' ');
	cmd = get_exec_cmd(args[0], envp, &err_code);
	if (cmd && (access(cmd, F_OK) == 0) && (access(cmd, X_OK) == -1))
	{
		free(cmd);
		exit_with_error_and_free("permission denied", args, 126);
	}
	if (cmd == NULL && err_code == ERROR_NO_FILE)
		exit_with_error_and_free(strerror(errno), args, 127);
	if (cmd == NULL)
		exit_with_error_and_free("command not found", args, 127);
	execve(cmd, args, envp);
	free(cmd);
	free_split(args);
	exit_with_error("execve error", NULL, 127);
}
