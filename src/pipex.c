/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:11:02 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/25 00:19:38 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_cmd(char *cmd, t_mshell_data *data)
{
	t_token *tokens;

	data->commands = NULL;
	data->n_cmds = 0;
	tokens = tokenize(cmd);
	if (!tokens)
		return (0);
	data->commands = create_commands_from_tokens(tokens, &data->n_cmds);
	free_tokens(tokens);
	if (!data->commands)
	{
		return (0);
	}
	return (1);
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
	return (status);
}

