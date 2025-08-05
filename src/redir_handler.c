/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:32:40 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/05 20:16:42 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static t_heredoc_fd	handle_input_redirection(const char *filename, t_heredoc_fd last_fd);
static int	handle_output_redirection(const char *filename, int last_fd);
static int	handle_append_redirection(const char *filename, int last_fd);
static t_heredoc_fd	handle_heredoc_redirection(const char *delimiter, t_heredoc_fd last_fd);

void	handle_redirections(t_list *redirs)
{
	t_list			*current;
	t_redir			*redir;
	t_heredoc_fd	fd_last_input;
	int				fd_last_output;

	current = redirs;
	fd_last_input.fd = -1;
	fd_last_output = -1;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->type == REDIR_INPUT)
			fd_last_input = handle_input_redirection(redir->filename, fd_last_input);
		else if (redir->type == REDIR_OUTPUT)
			fd_last_output = handle_output_redirection(redir->filename, fd_last_output);
		else if (redir->type == REDIR_APPEND)
			fd_last_output = handle_append_redirection(redir->filename, fd_last_output);
		else if (redir->type == REDIR_HEREDOC)
			fd_last_input = handle_heredoc_redirection(redir->heredoc_delimiter, fd_last_input);
		current = current->next;
	}
	if (fd_last_input.fd)
	{
		dup2(fd_last_input.fd, STDIN_FILENO);
		close(fd_last_input.fd);
		if (fd_last_input.is_heredoc)
			unlink(fd_last_input.filename);
	}
	if (fd_last_output)
	{
		dup2(fd_last_output, STDOUT_FILENO);
		close(fd_last_output);
	}
	
}

static t_heredoc_fd	handle_input_redirection(const char *filename, t_heredoc_fd last_fd)
{
	if (last_fd.fd)
	{
		close(last_fd.fd);
		if (last_fd.is_heredoc)
			unlink(last_fd.filename);
	}
	last_fd.fd = open(filename, O_RDONLY);
	last_fd.is_heredoc = 0;
	if (last_fd.fd < 0)
	{
		perror("open");
		exit(1);
	}
	return (last_fd);
}

static int	handle_output_redirection(const char *filename, int last_fd)
{
	if (last_fd)
		close(last_fd);
	last_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (last_fd < 0)
	{
		perror("open");
		exit(1);
	}
	return (last_fd);
}

static int	handle_append_redirection(const char *filename, int last_fd)
{
	if (last_fd)
		close(last_fd);
	last_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (last_fd < 0)
	{
		perror("open");
		exit(1);
	}
	return (last_fd);
}

char	*create_heredoc_filename(void)
{
	char			*filename;
	char			*counter_str;
	static int		counter = 0;
	struct stat		st;

	while (counter < 10000)
	{
		counter_str = ft_itoa(counter);
		if (!counter_str)
			return (NULL);
		filename = ft_strjoin(".heredoc_", counter_str);
		free(counter_str);
		if (!filename)
			return (NULL);
		if (stat(filename, &st) == -1)
		{
			counter++;
			return (filename);
		}
		free(filename);
		counter++;
	}
	return (NULL);
}

static t_heredoc_fd	handle_heredoc_redirection(const char *delimiter, t_heredoc_fd last_fd)
{
	if (last_fd.fd)
	{
		close(last_fd.fd);
		if (last_fd.is_heredoc)
			unlink(last_fd.filename);
	}
	last_fd.is_heredoc = 1;
	last_fd.filename = create_heredoc_filename();
	handle_heredoc(last_fd.filename, delimiter);
	last_fd.fd = open(last_fd.filename, O_RDONLY);
	if (last_fd.fd < 0)
	{
		perror("minishell");
		unlink(last_fd.filename);
		exit(1);
	}
	// unlink(filename);
	return (last_fd);
}
