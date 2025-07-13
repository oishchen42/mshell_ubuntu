/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:02:19 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/13 21:30:50 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static int	count_splits_cmd(char const *s, char c);
static void	fill_split(char **res, char const *s, char c);
static int	find_next_split_cmd(char const *s, char *c);
static void	suppress_mask_chars(char **str);

static int	count_splits_cmd(char const *s, char c)
{
	int		n_splits;
	int		i;
	char	to_find;

	to_find = c;
	if (!(*s))
		return (0);
	n_splits = 0;
	i = 1;
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'') && s[i - 1] != '\\')
		{
			if (to_find == s[i])
				to_find = c;
			else if (to_find == c)
				to_find = s[i];
		}
		if (s[i] == to_find && s[i - 1] != to_find && s[i - 1] != c)
			n_splits++;
		i++;
	}
	if (s[i - 1] != to_find)
		n_splits++;
	return (n_splits);
}

static void	fill_split(char **res, char const *s, char c)
{
	int		i;
	int		j;
	int		length;
	char	to_find;

	i = 0;
	j = 0;
	to_find = c;
	while (s[i])
	{
		while (s[i] == to_find && to_find == c)
			i++;
		if (s[i] == to_find && to_find != c)
			i++;
		if (!s[i])
			break ;
		length = find_next_split_cmd(&s[i], &to_find);
		if (length > 0)
		{
			res[j] = ft_substr(s, i, length);
			suppress_mask_chars(&res[j++]);
			i += length;
		}
	}
	res[j] = NULL;
}

static int	find_next_split_cmd(char const *s, char *c)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (s[i] && (s[i] != *c || ((s[i] == '"' || s[i] == '\'')
				&& s[i - 1] == '\\')))
	{
		if (*c == ' ' && ((s[i] == '"' || s[i] == '\'') && s[i - 1] != '\\'))
			break ;
		length++;
		i++;
	}
	if ((s[i] == '"' || s[i] == '\'') && s[i - 1] != '\\')
	{
		if (s[i] == *c)
			*c = ' ';
		else
			*c = s[i];
	}
	return (length);
}

static void	suppress_mask_chars(char **str)
{
	char	*p;
	int		i;

	if (!str || !(*str))
		return ;
	p = *str;
	while (*p && *(p + 1))
	{
		if (*p == '\\' && (*(p + 1) == '"' || *(p + 1) == '\''))
		{
			i = 0;
			while (p[i])
			{
				p[i] = p[i + 1];
				i++;
			}
		}
		else
			p++;
	}
}

char	**ft_split_cmd(char const *s, char c)
{
	int		n_splits;
	char	**res;

	n_splits = count_splits_cmd(s, c);
	res = (char **)malloc(sizeof(char *) * (n_splits + 1));
	if (!res)
		return (NULL);
	fill_split(res, s, c);
	return (res);
}
