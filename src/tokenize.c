/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:02:31 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/25 14:27:30 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static void		free_partial_tokens(t_token *tokens, int count);
static int		skip_whitespace(const char *input, int i, int len);
static int		find_token_end(const char *input, int start, int len,
					t_quote_state *token_quote);
static t_token	create_token(const char *input, int start, int end,
					t_quote_state token_quote);

t_token	*tokenize(const char *input)
{
	int			i;
	int			len;
	int			start;
	int			end;
	int			token_count;
	t_token		new_token;
	t_token		*tokens;
	t_quote_state	token_quote;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	tokens = (t_token *)malloc(sizeof(t_token) * (len + 1));
	if (!tokens)
		return (NULL);
	token_count = 0;
	i = 0;
	while (i < len)
	{
		i = skip_whitespace(input, i, len);
		if (i >= len)
			break ;
		start = i;
		end = find_token_end(input, start, len, &token_quote);
		new_token = create_token(input, start, end, token_quote);
		if (!new_token.content)
		{
			free_partial_tokens(tokens, token_count);
			return (NULL);
		}
		tokens[token_count++] = new_token;
		i = end;
	}
	tokens[token_count].content = NULL;
	tokens[token_count].quote_state = QUOTE_NONE;
	tokens[token_count].is_pipe = 0;
	return (tokens);
}

static int	skip_whitespace(const char *input, int i, int len)
{
	while (i < len && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
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
