/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:44:39 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/11 23:44:08 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c);

int	should_add_to_history(const char *line)
{
	if (!line)
		return (0);
	while (*line)
	{
		if (!ft_isspace((unsigned char)*line))
			return (1);
		line++;
	}
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' /*|| c == '\n'
		|| c == '\v' || c == '\f' || c == '\r'*/);
}
