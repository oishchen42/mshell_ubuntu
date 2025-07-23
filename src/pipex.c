/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:11:02 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/22 23:28:35 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipex	*init_pipex(char *cmd, char *envp[])
{
	t_pipex	*new_pipex;

	(void ) envp;
	new_pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!new_pipex)
		return (NULL);
	new_pipex->commands = create_commands_from_tokens(tokenize(cmd), &new_pipex->n_cmds);
	if (!new_pipex->commands)
	{
		free_pipex(new_pipex);
		return (NULL);
	}
	new_pipex->is_heredoc = 0;
	return (new_pipex);
}

int	wait_for_child_procs(int pids[], int size)
{
	int	i;
	int	status;

	if (!pids)
		return (EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		if (i == (size - 1))
			waitpid(pids[i], &status, 0);
		else
			waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
	return (status);
}

void	close_pipe(int fd[2])
{
	close(fd[READ_END]);
	close(fd[WRITE_END]);
}
