/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:37:28 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/06 21:11:21 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_cu;
	const unsigned char	*src_cu;
	size_t				i;

	dst_cu = (unsigned char *) dst;
	src_cu = (unsigned char *) src;
	if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			dst_cu[i] = src_cu[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			dst_cu[len] = src_cu[len];
	}
	return (dst);
}
