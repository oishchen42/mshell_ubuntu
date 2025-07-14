/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:11:02 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/13 23:41:49 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_size(char **arr);

t_pipex	*init_pipex(char *cmd, char *envp[])
{
	t_pipex	*new_pipex;

	new_pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!new_pipex)
		return (NULL);
	new_pipex->infile = NULL;
	new_pipex->cmds = ft_split(cmd, '|');
	if (!new_pipex->cmds)
	{
		free_pipex(new_pipex);
		return (NULL);
	}
	new_pipex->n_cmds = split_size(new_pipex->cmds);
	new_pipex->envp = envp;
	new_pipex->infile = NULL;
	new_pipex->outfile = NULL;
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

static int	split_size(char **arr)
{
	int	size;

	if (!arr)
		return (0);
	size = 0;
	while (arr[size])
		size++;
	return (size);
}