/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:20:48 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/07 13:22:36 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_cu;
	unsigned char	*s2_cu;

	s1_cu = (unsigned char *) s1;
	s2_cu = (unsigned char *) s2;
	while (n > 0)
	{
		if (*s1_cu != *s2_cu)
			return (*s1_cu - *s2_cu);
		s1_cu++;
		s2_cu++;
		n--;
	}
	return (0);
}
