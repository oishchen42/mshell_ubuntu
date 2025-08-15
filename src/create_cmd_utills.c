/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_utills.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:02:35 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/11 19:09:18 by nmikuka          ###   ########.fr       */
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

void	suppress_quotes(char *str, int *has_quotes)
{
	int	i;
	int	j;
	t_quote_state quote_state;
	char c;

	i = 0;
	j = 0;
	quote_state = QUOTE_NONE;
	*has_quotes = 0;
	while (str[i])
	{
		c = str[i];
		if (update_quote_state(c, &quote_state))
		{
			*has_quotes = 1;
			i++;
			continue;
		}
		str[j++] = str[i++];
	}
	str[j] = '\0';
}

/**
 * Creates a command array from tokens (until pipe or end)
 */
t_command	create_command_from_tokens(t_token *tokens, int start, t_mshell_data *data)
{
	t_command	cmd;
	int			i;
	int			arg_index;
	int			token_count;
	// char		*path;
	
	cmd.args = NULL;
	if (tokens[start].is_pipe)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		data->exit_code = 2;
		return (cmd);
	}
	token_count = count_tokens_until_pipe(tokens, start);
	if (token_count == 0)
		return (cmd);

	cmd.args = malloc(sizeof(char *) * (token_count + 1));
	ft_bzero(cmd.args, sizeof(char *) * (token_count + 1));
	cmd.redirections = NULL;
	if (!cmd.args)
	{
		perror("minishell: malloc");
		return (cmd);
	}
	i = start;
	arg_index = 0;
	while (tokens[i].content && !tokens[i].is_pipe)
	{
		if (tokens[i].redir_type != REDIR_NONE)
		{
			if (add_redirection(&(cmd.redirections), tokens, i, tokens[i + 1].content))
			{
				ft_lstclear(&(cmd).redirections, free_redir_content);
				free_command(&cmd);
				ft_putendl_fd("minishell: create command: syntax error", 2);
				data->exit_code = 2;
				return (cmd);
			}
			i += 2;
			continue ;
		}
		cmd.args[arg_index] = ft_strdup(tokens[i].content);
		if (!cmd.args[arg_index])
		{
			ft_lstclear(&(cmd).redirections, free_redir_content);
			free_command(&cmd);
			return (cmd);
		}
		i++;
		arg_index++;
	}
	cmd.args[arg_index] = NULL;
	return (cmd);
}

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
t_command	*create_commands_from_tokens(t_token *tokens, int *n_cmds, t_mshell_data *data)
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
		commands[cmd_index] = create_command_from_tokens(tokens, token_index, data);
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
		// print_redirections(cmds[i].redirections);
		ft_lstclear(&(cmds[i]).redirections, free_redir_content);
		free_command(&cmds[i]);
		i++;
	}
	free(cmds);
}
