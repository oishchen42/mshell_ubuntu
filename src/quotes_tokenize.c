/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:02:31 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/20 12:12:12 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "libft.h"

static void		free_partial_tokens(t_token *tokens, int count);
static int		skip_whitespace(const char *input, int i, int len);
static int		find_token_end(const char *input, int start, int len,
					quote_state *token_quote);
static t_token	create_token(const char *input, int start, int end,
					quote_state token_quote);

t_token	*tokenize(const char *input)
{
	int			i;
	int			len;
	int			start;
	int			end;
	int			token_count;
	t_token		new_token;
	t_token		*tokens;
	quote_state	token_quote;

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
		quote_state *token_quote)
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
		quote_state token_quote)
{
	t_token	new_token;
	int		token_len;

	new_token.content = NULL;
	new_token.quote_state = token_quote;
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
	if (token_quote == QUOTE_NONE && ft_strncmp(new_token.content, "|", 2) == 0)
		new_token.is_pipe = 1;
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

int	check_quote_balance(const char *input)
{
	int			i;
	int			len;
	char		c;
	quote_state	state;

	if (!input)
		return (1);
	len = strlen(input);
	state = QUOTE_NONE;
	i = 0;
	while (i < len)
	{
		c = input[i];
		if (state == QUOTE_NONE)
		{
			if (c == '\'')
				state = QUOTE_SINGLE;
			else if (c == '"')
				state = QUOTE_DOUBLE;
		}
		else if (state == QUOTE_SINGLE && c == '\'')
			state = QUOTE_NONE;
		else if (state == QUOTE_DOUBLE && c == '"')
			state = QUOTE_NONE;
		i++;
	}
	return (state == QUOTE_NONE);
}
