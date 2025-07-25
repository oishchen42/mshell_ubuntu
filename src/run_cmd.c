/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:42:03 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/25 14:20:02 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static void	save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

static void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	run_pipex(t_mshell_data *mshell_struct)
{
	int		**pipes;
	pid_t	*pids;
	int		i;
	int		j;
	int		n_cmds = mshell_struct->n_cmds;
	int		builtin_status;
	int	saved_stdin, saved_stdout;
	
	if (!n_cmds)
		return (EXIT_SUCCESS);
	if (n_cmds == 1 && is_builtin(mshell_struct->commands[0]))
	{
		save_std_fds(&saved_stdin, &saved_stdout);
		handle_redirections(mshell_struct->commands[0].redirections);
		builtin_status = parse_builtin(mshell_struct->commands[0], mshell_struct);
		restore_std_fds(saved_stdin, saved_stdout);
		return (builtin_status);
	}
	pipes = malloc(sizeof(int *) * (n_cmds - 1));
	pids = malloc(sizeof(pid_t) * n_cmds);
	i = 0;
	while (i < n_cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
			return (EPIPE);
		i++;
	}
	// Fork all children
	i = 0;
	while (i < n_cmds)
	{	
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i > 0)
				dup2(pipes[i - 1][READ_END], STDIN_FILENO);
			if (i < n_cmds - 1)
				dup2(pipes[i][WRITE_END], STDOUT_FILENO);
			// Close all pipes in child
			j = 0;
			while (j < n_cmds - 1)
			{
				close(pipes[j][READ_END]);
				close(pipes[j][WRITE_END]);
				j++;
			}
			run_cmd(mshell_struct->commands[i], mshell_struct);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	// Parent: close all pipes
	i = 0;
	while (i < n_cmds - 1)
	{
		close(pipes[i][READ_END]);
		close(pipes[i][WRITE_END]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
	// Wait for all children
	int status = wait_for_child_procs(pids, n_cmds);
	free(pids);
	return (status);
}

void	run_cmd(t_command command, t_mshell_data *mshell_struct)
{
	char	*cmd;
	int		err_code;
	int		builtin_status;
    
    handle_redirections(command.redirections);
	if (!command.args || !command.args[0])
        exit(0);
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
	exit_with_error("execve error", NULL, 126);
}
