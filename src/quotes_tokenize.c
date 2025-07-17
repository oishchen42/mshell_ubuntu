/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:02:31 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/17 23:34:27 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "libft.h"

static void	free_partial_tokens(char **tokens, int count);
static int	skip_whitespace(const char *input, int i, int len);
static int	find_token_end(const char *input, int start, int len, quote_state *token_quote);
static char	*create_token(const char *input, int start, int end, quote_state token_quote);

char **tokenize(const char *input)
{
	int		i;
	int		len;
	int		start;
	int		end;
	int		token_count;
	char	*new_token;
	char	**tokens;
	quote_state token_quote;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	tokens = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tokens)
		return (NULL);
	token_count = 0;
	i = 0;
	while (i < len) {
		i = skip_whitespace(input, i, len);
		if (i >= len)
			break ;
		start = i;
		end = find_token_end(input, start, len, &token_quote);
		new_token = create_token(input, start, end, token_quote);
		if (!new_token) {
			free_partial_tokens(tokens, token_count);
			return  (NULL);
		}
		tokens[token_count++] = new_token;
		i = end;
	}
	tokens[token_count] = NULL;
	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	return (tokens);
}

static int skip_whitespace(const char *input, int i, int len)
{
	while (i < len && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return i;
}

static int find_token_end(const char *input, int start, int len, quote_state *token_quote)
{
	int			i;
	quote_state	first_quote;
	char c;

	first_quote = QUOTE_NONE;
	if (input[start] == '\'')
		first_quote = QUOTE_SINGLE;
	else if (input[start] == '"')
		first_quote = QUOTE_DOUBLE;
	i = start + 1;
	while (i < len)
	{
		c = input[i];
		if (first_quote == QUOTE_NONE)
		{
			if (c == ' ' || c == '\t')
				break ;
		}
		else if ((first_quote == QUOTE_SINGLE && c == '\'')
				|| (first_quote == QUOTE_DOUBLE && c == '"'))
		{
			i++;
			break ;
		}
		else if (first_quote == QUOTE_DOUBLE && c == '\\' && i + 1 < len)
			i++;
		i++;
	}
	*token_quote = first_quote;
	return (i);
}

static char *create_token(const char *input, int start, int end, quote_state token_quote)
{
	char *new_token;

	new_token = NULL;
	if (token_quote != QUOTE_NONE)
	{
		start++;
		end--;
	}
	int token_len = end - start;
	char *raw_token = malloc(token_len + 1);
	if (!raw_token)
		return new_token;
	ft_strlcpy(raw_token, input + start, token_len + 1);
	raw_token[token_len] = '\0';
	new_token = raw_token;
	return new_token;
}

/**
 * Frees allocated tokens on error
 */
static void free_partial_tokens(char **tokens, int count)
{
	int i;

	i = 0;
	while (i < count) {
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int check_quote_balance(const char *input)
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
