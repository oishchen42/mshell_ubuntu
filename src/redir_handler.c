/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:32:40 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/25 14:05:25 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_input_redirection(const char *filename);
static void	handle_output_redirection(const char *filename);
static void	handle_append_redirection(const char *filename);
static void	handle_heredoc_redirection(const char *delimiter);

void	handle_redirections(t_list *redirs)
{
	t_list	*current;
	t_redir	*redir;

	current = redirs;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->type == REDIR_INPUT)
			handle_input_redirection(redir->filename);
		else if (redir->type == REDIR_OUTPUT)
			handle_output_redirection(redir->filename);
		else if (redir->type == REDIR_APPEND)
			handle_append_redirection(redir->filename);
		else if (redir->type == REDIR_HEREDOC)
			handle_heredoc_redirection(redir->heredoc_delimiter);
		current = current->next;
	}
}

static void	handle_input_redirection(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_output_redirection(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_append_redirection(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_heredoc_redirection(const char *delimiter)
{
	int	fd;

	handle_heredoc("_temp", delimiter);
	fd = open("_temp", O_RDONLY);
	if (fd < 0)
	{
		perror("open heredoc temp file");
		unlink("_temp");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink("_temp");
}
