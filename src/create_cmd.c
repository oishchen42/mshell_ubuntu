/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:11:02 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/14 17:27:26 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	parse_cmd(char *cmd, t_mshell_data *data)
{
	t_token	*tokens;
	t_token	*tokens_split;
	char	*expand_vars;
	int		i;

	data->commands = NULL;
	data->n_cmds = 0;
	tokens = split_pipes_and_redirs(cmd);
	i = 0;
	while (tokens[i].content)
	{
		expand_vars = expand_variables(tokens[i].content, data);
		if (!expand_vars)
		{
			free_tokens(tokens);
			return (0);
		}
		free(tokens[i].content);
		tokens[i].content = expand_vars;
		i++;
	}
	tokens_split = split_args_by_space(tokens);
	free_tokens(tokens);
	i = 0;
	while (tokens_split[i].content)
	{
		suppress_quotes(tokens_split[i].content, &tokens_split[i].has_quotes);
		i++;
	}
	if (!tokens_split)
		return (0);
	data->commands = create_commands_from_tokens(tokens_split, &data->n_cmds, data);
	free_tokens(tokens_split);
	if (!data->commands)
		return (0);
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
	return (WEXITSTATUS(status));
}
