/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:12:24 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/07 19:57:36 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	to_copy;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	dst += dst_len;
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	else
		to_copy = dstsize - dst_len;
	while (to_copy > 1 && *src)
	{
		*dst = *src;
		dst++;
		src++;
		to_copy--;
	}
	if (to_copy > 0)
		*dst = '\0';
	return (dst_len + src_len);
}
