/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:02:19 by nmikuka           #+#    #+#             */
/*   Updated: 2025/06/29 21:15:25 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line/get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}

int	count_splits(char const *s, char c)
{
	int		n_splits;
	int		i;

	if (!(*s))
		return (0);
	n_splits = 0;
	i = 1;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			n_splits++;
		i++;
	}
	if (s[i - 1] != c)
		n_splits++;
	return (n_splits);
}

int	find_next_split(char const *s, char c)
{
	int	length;

	length = 0;
	while (*s && *s != c)
	{
		length++;
		s++;
	}
	return (length);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		length;
	int		n_splits;
	char	**res;

	n_splits = count_splits(s, c);
	res = (char **)malloc(sizeof(char *) * (n_splits + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		length = find_next_split(&s[i], c);
		res[j] = ft_substr(s, i, length);
		j++;
		i += length;
	}
	res[j] = NULL;
	return (res);
}

void	free_split(char	**split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
