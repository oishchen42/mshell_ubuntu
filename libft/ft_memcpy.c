/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:11:46 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/06 20:36:30 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	unsigned char		*dst_cu;
	const unsigned char	*src_cu;

	dst_cu = (unsigned char *) dst;
	src_cu = (unsigned char *) src;
	while (n > 0)
	{
		*dst_cu++ = *src_cu++;
		n--;
	}
	return (dst);
}
