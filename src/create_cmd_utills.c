/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_utills.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:02:35 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/01 09:45:58 by nmikuka          ###   ########.fr       */
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
t_command	create_command_from_tokens(t_token *tokens, int start, t_mshell_data *data)
{
	t_command	cmd;
	int			i;
	int			arg_index;
	int			token_count;
	char		*str;

	cmd.args = NULL;
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
			add_redirection(&(cmd.redirections), tokens, i);
			i += 2;
			continue ;
		}
		if (tokens[i].quote_state == QUOTE_NONE && (ft_strncmp(tokens[i].content, "~", 2) == 0
				|| ft_strncmp(tokens[i].content, "~/", 2) == 0))
			str = ft_strjoin(ft_getenv("HOME", data->env), &(tokens[i].content)[1]);
		else if (tokens[i].quote_state != QUOTE_SINGLE && ft_strchr(tokens[i].content, '$'))
		{
			str = expand_variables(tokens[i].content, data);
			if (str && !tokens[i].ends_with_space && tokens[i + 1].content) //suppress last dollar sign if there is next token without space
			{
				int len = ft_strlen(str);
				if (str[len - 1] == '$')
					str[len - 1] = '\0';
			}
		}
		else
			str = ft_strdup(tokens[i].content);
		if (cmd.args[arg_index])
		{
			char *old_cmd = cmd.args[arg_index];
			cmd.args[arg_index] = ft_strjoin(old_cmd, str);
			free (old_cmd);
		}	
		else
			cmd.args[arg_index] = ft_strdup(str);
		if (str)
			free (str);
		if (!cmd.args[arg_index])
		{
			perror("minishell: strdup");
			free_command(&cmd);
			return (cmd);
		}
		if (tokens[i].ends_with_space || !tokens[i + 1].content)
			arg_index++;
		i++;
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
		free_command(&cmds[i]);
		ft_lstclear(&(cmds[i]).redirections, free_redir_content);
		i++;
	}
	free(cmds);
}
