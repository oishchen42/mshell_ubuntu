/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:02:35 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/28 12:19:41 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

void	free_command(t_command *cmd);
void	free_commands(t_command *commands, int n_cmds);

/**
 * Counts tokens until next pipe or end
 */
int	count_tokens_until_pipe(t_token *tokens, int start)
{
	int	i;

	i = start;
	while (tokens[i].content && !tokens[i].is_pipe)
		i++;
	return (i - start);
}

/**
 * Creates a command array from tokens (until pipe or end)
 */
t_command	create_command_from_tokens(t_token *tokens, int start, char **envp)
{
	t_command	cmd;
	int			i;
	int			arg_index;
	int			token_count;

	cmd.args = NULL;
	token_count = count_tokens_until_pipe(tokens, start);
	if (token_count == 0)
		return (cmd);
	cmd.args = malloc(sizeof(char *) * (token_count + 1));
	if (!cmd.args)
	{
		perror("minishell: malloc");
		return (cmd);
	}
	i = start;
	arg_index = 0;
	while (tokens[i].content && !tokens[i].is_pipe)
	{
		if (tokens[i].quote_state != QUOTE_SINGLE && ft_strchr(tokens[i].content, '$'))
			cmd.args[arg_index] = expand_variables(tokens[i].content, envp);
		else
			cmd.args[arg_index] = ft_strdup(tokens[i].content);
		if (!cmd.args[arg_index])
		{
			perror("minishell: strdup");
			free_command(&cmd);
			return (cmd);
		}
		arg_index++;
		i++;
	}
	cmd.args[arg_index] = NULL;
	return (cmd);
}

/**
 * Count pipes in token array
 */
int	count_pipes(t_token *tokens)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (tokens[i].content)
	{
		if (tokens[i].is_pipe)
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

/**
 * Creates commands array from tokens and returns number of commands
 * Returns NULL on error, sets n_cmds to 0
 */
t_command	*create_commands_from_tokens(t_token *tokens, int *n_cmds, char **envp)
{
	int			token_index;
	int			cmd_index;
	t_command	*commands;

	if (!tokens || !n_cmds)
	{
		*n_cmds = 0;
		return (NULL);
	}
	*n_cmds = count_pipes(tokens) + 1;
	commands = malloc(sizeof(t_command) * (*n_cmds));
	if (!commands)
	{
		perror("minishell: malloc");
		*n_cmds = 0;
		return (NULL);
	}
	token_index = 0;
	cmd_index = 0;
	while (tokens[token_index].content && cmd_index < *n_cmds)
	{
		commands[cmd_index] = create_command_from_tokens(tokens, token_index, envp);
		if (!commands[cmd_index].args)
		{
			free_commands(commands, cmd_index);
			*n_cmds = 0;
			return (NULL);
		}
		while (tokens[token_index].content && !tokens[token_index].is_pipe)
			token_index++;
		if (tokens[token_index].content && tokens[token_index].is_pipe)
			token_index++;
		cmd_index++;
	}
	return (commands);
}

void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	cmd->args = NULL;
}

void	free_commands(t_command *cmds, int n_cmds)
{
	int	i;

	if (!cmds)
		return ;
	i = 0;
	while (i < n_cmds)
	{
		free_command(&cmds[i]);
		i++;
	}
	free(cmds);
}
