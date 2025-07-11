/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:20:23 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/10 14:31:01 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_length(int n)
{
	int	l;

	if (n == 0)
		return (1);
	l = 0;
	if (n < 0)
	{
		n *= -1;
		l++;
	}
	while (n > 0)
	{
		n /= 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int		l;
	int		neg;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = (n < 0);
	l = get_length(n);
	res = (char *)malloc(sizeof(char) * (l + 1));
	if (!res)
		return (NULL);
	res[l] = '\0';
	if (neg)
	{
		res[0] = '-';
		n *= -1;
	}
	while (--l >= neg)
	{
		res[l] = '0' + n % 10;
		n /= 10;
	}
	return (res);
}
