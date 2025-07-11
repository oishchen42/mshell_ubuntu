/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:08:24 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/07 20:14:27 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occ;

	last_occ = NULL;
	while (*s)
	{
		if (*s == c)
			last_occ = (char *)s;
		s++;
	}
	if (c == '\0' && *s == c)
		last_occ = (char *)s;
	return (last_occ);
}
