/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:43:18 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/25 13:54:41 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

int	check_quote_balance(const char *input)
{
	char			c;
	t_quote_state	state;

	if (!input)
		return (1);
	state = QUOTE_NONE;
	while (*input)
	{
		c = *input;
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
		input++;
	}
	return (state == QUOTE_NONE);
}

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].content)
	{
		free(tokens[i].content);
		i++;
	}
	free(tokens);
}
