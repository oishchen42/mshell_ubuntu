/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:02:31 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/30 17:02:57 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static int		parse_tokens(const char *input, int len, t_token *tokens);
static void		free_partial_tokens(t_token *tokens, int count);
static int		find_token_end(const char *input, int start, int len,
					t_quote_state *token_quote);
static t_token	create_token(const char *input, int start, int end,
					t_quote_state token_quote);

t_token	*tokenize(const char *input)
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
		i = skip_whitespace(input, i, len);
		if (i >= len)
			break ;
		end = find_token_end(input, i, len, &token_quote);
		tokens[token_count] = create_token(input, i, end, token_quote);
		if (!tokens[token_count].content)
		{
			free_partial_tokens(tokens, token_count);
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
	if (input[start] == '\'')
		*token_quote = QUOTE_SINGLE;
	else if (input[start] == '"')
		*token_quote = QUOTE_DOUBLE;
	else if (input[start] == '|')
		return (start + 1);
	else if (get_redir_type(input + start) == REDIR_APPEND
		|| get_redir_type(input + start) == REDIR_HEREDOC)
		return (start + 2);
	else if (get_redir_type(input + start) == REDIR_INPUT
		|| get_redir_type(input + start) == REDIR_OUTPUT)
		return (start + 1);
	i = start + 1;
	while (i < len)
	{
		c = input[i];
		if (*token_quote == QUOTE_NONE)
		{
			if (c == ' ' || c == '\t' || c == '\'' || c == '"')
				break ;
			if (c == '|')
				break ;
			if (c == '<' || c == '>')
				break ;
		}
		else if ((*token_quote == QUOTE_SINGLE && c == '\'')
			|| (*token_quote == QUOTE_DOUBLE && c == '"'))
		{
			i++;
			break ;
		}
		else if (*token_quote == QUOTE_DOUBLE && c == '\\' && i + 1 < len)
			i++;
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
	new_token.quote_state = token_quote;
	new_token.redir_type = REDIR_NONE;
	new_token.is_pipe = 0;
	new_token.ends_with_space = input[end] && ft_isspace(input[end]);
	if (token_quote != QUOTE_NONE)
	{
		start++;
		end--;
	}
	token_len = end - start;
	new_token.content = malloc(token_len + 1);
	if (!new_token.content)
		return (new_token);
	ft_strlcpy(new_token.content, input + start, token_len + 1);
	new_token.content[token_len] = '\0';
	if (token_quote == QUOTE_NONE)
	{
		if (ft_strncmp(new_token.content, "|", 2) == 0)
			new_token.is_pipe = 1;
		new_token.redir_type = get_redir_type(new_token.content);
	}
	return (new_token);
}

/**
 * Frees allocated tokens on error
 */
static void	free_partial_tokens(t_token *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tokens[i].content);
		i++;
	}
	free(tokens);
}
