/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:19:28 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/17 12:15:34 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strljoin(char const *s1, char const *s2, size_t l)
{
	char	*res;
	size_t	len1;

	len1 = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (len1 + l + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, len1 + 1);
	ft_strlcpy(res + len1, s2, l + 1);
	return (res);
}

int	ft_strlen(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cu;

	cu = (unsigned char *) b;
	while (len > 0)
	{
		*cu = (unsigned char) c;
		cu++;
		len--;
	}
	return (b);
}
