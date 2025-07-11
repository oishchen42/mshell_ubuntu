/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:49:00 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/06 23:00:15 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	cu;

	cu = (unsigned char) c;
	while (n > 0)
	{
		if (*((unsigned char *) s) == cu)
			return ((void *) s);
		n--;
		s++;
	}
	return (NULL);
}
