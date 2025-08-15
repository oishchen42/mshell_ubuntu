/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:02:31 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/13 14:11:43 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static int		parse_tokens(const char *input, int len, t_token *tokens);
static t_token	create_token(const char *input, int start, int end,
					t_quote_state token_quote);
static int		find_token_end(const char *input, int start, int len,
					t_quote_state *token_quote);
static int		len_redir_sign(const char *input);

t_token	*split_pipes_and_redirs(const char *input)
{
	int		len;
	t_token	*tokens;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	tokens = (t_token *)malloc(sizeof(t_token) * (len + 1));
	if (!tokens)
		return (NULL);
	ft_bzero(tokens, sizeof(t_token) * (len + 1));
	if (!parse_tokens(input, len, tokens))
	{
		free(tokens);
		return (NULL);
	}
	// int i = 0;
	// while (tokens[i].content)
	// {
	// 	printf("%s\n", tokens[i++].content);
	// }
	return (tokens);
}

static int	parse_tokens(const char *input, int len, t_token *tokens)
{
	int				i;
	int				end;
	int				token_count;
	t_quote_state	token_quote;

	token_count = 0;
	i = 0;
	while (i < len)
	{
		end = find_token_end(input, i, len, &token_quote);
		tokens[token_count] = create_token(input, i, end, token_quote);
		if (!tokens[token_count].content)
		{
			free_tokens(tokens);
			return (0);
		}
		token_count++;
		i = end;
	}
	tokens[token_count].content = NULL;
	return (1);
}

static int	find_token_end(const char *input, int start, int len,
		t_quote_state *token_quote)
{
	int		i;
	char	c;

	*token_quote = QUOTE_NONE;
	if (input[start] == '|')
		return (start + 1);
	else if (get_redir_type(input + start))
		return (start + len_redir_sign(input + start));
	i = start;
	while (i < len)
	{
		c = input[i];
		update_quote_state(c, token_quote);
		if (*token_quote == QUOTE_NONE)
		{
			if (c == '|' || c == '<' || c == '>')
				return (i);
		}
		i++;
	}
	return (i);
}

static t_token	create_token(const char *input, int start, int end,
		t_quote_state token_quote)
{
	t_token	new_token;
	int		token_len;

	new_token.content = NULL;
	new_token.redir_type = REDIR_NONE;
	new_token.is_pipe = 0;
	token_len = end - start;
	new_token.content = malloc(token_len + 1);
	if (!new_token.content)
		return (new_token);
	ft_strlcpy(new_token.content, input + start, token_len + 1);
	if (token_quote == QUOTE_NONE)
	{
		if (ft_strncmp(new_token.content, "|", 2) == 0)
			new_token.is_pipe = 1;
		new_token.redir_type = get_redir_type(new_token.content);
	}
	return (new_token);
}

static int	len_redir_sign(const char *input)
{
	t_redir_type	redir;

	redir = get_redir_type(input);
	if (redir == REDIR_INPUT || redir == REDIR_OUTPUT)
		return (1);
	if (redir == REDIR_APPEND || redir == REDIR_HEREDOC)
		return (2);
	return (0);
}

// Frees allocated tokens on error
// static void	free_partial_tokens(t_token *tokens, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		free(tokens[i].content);
// 		i++;
// 	}
// 	free(tokens);
// }
