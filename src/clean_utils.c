/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:38:33 by oishchen          #+#    #+#             */
/*   Updated: 2025/07/18 20:06:10 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char	**split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_pipex(t_pipex	*pipex)
{
	// int	i;

	if (!pipex)
		return ;
	// i = 0;
	// while (pipex->cmds[i])
	// 	free(pipex->cmds[i++]);
	free(pipex);
}