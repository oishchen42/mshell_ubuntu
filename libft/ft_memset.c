/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:08:11 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/06 19:59:01 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
