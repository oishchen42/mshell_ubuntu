/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:06:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/09 14:36:27 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_in_charset(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	end;
	int	start;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && is_in_charset(s1[start], set))
		start++;
	while (end >= start && is_in_charset(s1[end], set))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
