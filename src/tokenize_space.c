/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:43:18 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/13 14:22:42 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static int	get_num_spaces(t_token *tokens);
static int	split_single_token(t_token token, t_token *new_tokens, int *j);
static int	find_next_space(char *str);

t_token	*split_args_by_space(t_token *tokens)
{
	int		len;
	t_token	*new_tokens;
	int		i;
	int		j;

	len = get_num_spaces(tokens);
	new_tokens = (t_token *)malloc(sizeof(t_token) * (len + 1));
	if (!new_tokens)
		return (NULL);
	ft_bzero(new_tokens, sizeof(t_token) * (len + 1));
	i = 0;
	j = 0;
	while (tokens[i].content)
	{
		if (!split_single_token(tokens[i], new_tokens, &j))
		{
			free_tokens(new_tokens);
			return (NULL);
		}
		i++;
	}
	new_tokens[j].content = NULL;
	// i = 0;
	// while (new_tokens[i].content)
	// {
	// 	printf("%s %i\n", new_tokens[i].content, i);
	// 	i++;
	// }
	return (new_tokens);
}

static int	get_num_spaces(t_token *tokens)
{
	int	num;
	int	i;
	int	j;

	num = 0;
	i = 0;
	while (tokens[i].content)
	{
		num++;
		j = 0;
		while (tokens[i].content[j])
		{
			if (ft_isspace(tokens[i].content[j]))
				num++;
			j++;
		}
		i++;
	}
	return (num);
}

static int	split_single_token(t_token token, t_token *new_tokens, int *j)
{
	int		i;
	int		len;
	char	*str;

	str = token.content;
	i = 0;
	while (str[i])
	{
		len = find_next_space(&str[i]);
		if (len > 0)
		{
			new_tokens[*j].is_pipe = token.is_pipe;
			new_tokens[*j].redir_type = token.redir_type;
			new_tokens[*j].content = malloc(sizeof(char) * (len + 1));
			ft_strlcpy(new_tokens[*j].content, &str[i], len + 1);
			if (!new_tokens[*j].content)
				return (0);
			(*j)++;
		}
		i += len;
		if (ft_isspace(str[i]))
			i++;
	}
	return (1);
}

static int	find_next_space(char *str)
{
	int				i;
	t_quote_state	quote_state;

	quote_state = QUOTE_NONE;
	i = 0;
	while (str[i])
	{
		update_quote_state(str[i], &quote_state);
		if (ft_isspace(str[i]) && quote_state == QUOTE_NONE)
			return (i);
		i++;
	}
	return (i);
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
