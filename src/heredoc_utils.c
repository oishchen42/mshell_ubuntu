/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:45:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/24 14:32:43 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_getline(void);
static char	*read_line(char *buffer, int buffer_size);
static char	*duplicate_buffer_size(char *buffer, int *buffer_size);
static char	*free_buffer(char *buffer);

void	handle_heredoc(char *heredoc_name, char *delimiter)
{
	int		fd;
	char	*next_line;

	fd = open(heredoc_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit_with_error("Error creating heredoc file", NULL, EXIT_FAILURE);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2); 
		next_line = ft_getline();
		if (!next_line)
			break ;
		if (ft_strncmp(next_line, delimiter, ft_strlen(delimiter)) == 0
			&& next_line[ft_strlen(delimiter)] == '\n')
			break ;
		write(fd, next_line, ft_strlen(next_line));
		free(next_line);
	}
	if (next_line)
		free(next_line);
	close(fd);
}

static char	*ft_getline(void)
{
	char	*buffer;
	int		buffer_size;

	buffer_size = 1 << 4;
	buffer = (char *)malloc(sizeof(char) * buffer_size);
	if (!buffer)
		return (NULL);
	buffer = read_line(buffer, buffer_size);
	return (buffer);
}

static char	*read_line(char *buffer, int buffer_size)
{
	char	c;
	int		read_bytes;
	int		i;

	read_bytes = read(STDIN_FILENO, &c, 1);
	i = 0;
	while (read_bytes > 0)
	{
		if (i >= (buffer_size - 1))
		{
			buffer = duplicate_buffer_size(buffer, &buffer_size);
			if (!buffer)
				return (NULL);
		}
		buffer[i++] = c;
		if (c == '\n')
			break ;
		read_bytes = read(STDIN_FILENO, &c, 1);
	}
	if (read_bytes <= 0 && i == 0)
		return (free_buffer(buffer));
	buffer[i] = '\0';
	return (buffer);
}

static char	*duplicate_buffer_size(char *buffer, int *buffer_size)
{
	int		new_size;
	char	*new_buffer;

	if (!buffer)
		return (NULL);
	new_size = *buffer_size * 2;
	new_buffer = (char *)malloc(sizeof(char) * new_size);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	ft_strlcpy(new_buffer, buffer, *buffer_size);
	free(buffer);
	*buffer_size = new_size;
	return (new_buffer);
}

static char	*free_buffer(char *buffer)
{
	if (buffer)
		free(buffer);
	return (NULL);
}
