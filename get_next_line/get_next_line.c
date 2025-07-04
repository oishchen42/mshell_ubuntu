/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:19:31 by nmikuka           #+#    #+#             */
/*   Updated: 2025/06/30 10:35:23 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

ssize_t	find_eol(char *s, size_t start)
{
	ssize_t	i;

	if (!s)
		return (-1);
	i = start;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

ssize_t	read_next_block(int fd, char *buffer, size_t *last_eol)
{
	ssize_t	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_memset(buffer, '\0', BUFFER_SIZE);
		return (0);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read >= 0)
		buffer[bytes_read] = '\0';
	else
		ft_memset(buffer, '\0', BUFFER_SIZE);
	*last_eol = 0;
	return (bytes_read);
}

char	*join_and_free(char *s, char *buffer, size_t *start, ssize_t end)
{
	char	*res;

	if (!buffer || !buffer[*start])
		return (s);
	if (end < 0)
		res = ft_strljoin(s, &buffer[*start], ft_strlen(buffer) - *start);
	else
	{
		res = ft_strljoin(s, &buffer[*start], end - *start + 1);
		*start = end + 1;
	}
	if (s)
		free(s);
	return (res);
}

char	*ft_free(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	char			*next_line;
	ssize_t			eol;
	static size_t	last_eol;
	ssize_t			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	eol = find_eol(buffer, last_eol);
	next_line = NULL;
	while (eol < 0)
	{
		next_line = join_and_free(next_line, buffer, &last_eol, eol);
		bytes_read = read_next_block(fd, buffer, &last_eol);
		if (bytes_read < 0)
			return (ft_free(next_line));
		if (bytes_read == 0)
			return (next_line);
		eol = find_eol(buffer, last_eol);
	}
	next_line = join_and_free(next_line, buffer, &last_eol, eol);
	return (next_line);
}
