/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:32:40 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/11 19:15:59 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	handle_input_redirection(const char *filename, int is_last_redir);
static int	handle_output_redirection(const char *filename, int is_last_redir);
static int	handle_append_redirection(const char *filename, int is_last_redir);
static int	handle_heredoc_redirection(const char *delimiter, t_mshell_data *data, int is_last_redir, int has_quotes);
void	mark_last_redirections(t_list *redirs);

int	handle_redirections(t_list *redirs, t_mshell_data *data)
{
	t_list	*current;
	t_redir	*redir;
	int		status;

	mark_last_redirections(redirs);
	current = redirs;
	status = 0;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->type == REDIR_INPUT)
			status = handle_input_redirection(redir->filename, redir->is_last_redir);
		else if (redir->type == REDIR_OUTPUT)
			status = handle_output_redirection(redir->filename, redir->is_last_redir);
		else if (redir->type == REDIR_APPEND)
			status = handle_append_redirection(redir->filename, redir->is_last_redir);
		else if (redir->type == REDIR_HEREDOC)
			status = handle_heredoc_redirection(redir->heredoc_delimiter, data, redir->is_last_redir, redir->has_quotes);
		else
			status = -1;
		if (status == -1)
			return (-1);
		current = current->next;
	}
	return (status);
}

void	mark_last_redirections(t_list *redirs)
{
	t_list	*current;
	t_redir	*redir;
	t_list	*last_stdin;
	t_list	*last_stdout;

	if (!redirs)
		return;
	last_stdin = NULL;
	last_stdout = NULL;
	current = redirs;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir)
		{
			redir->is_last_redir = 0;
			if (redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC)
				last_stdin = current;
			else if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
				last_stdout = current;
		}
		current = current->next;
	}
	if (last_stdin)
	{
		redir = (t_redir *)last_stdin->content;
		redir->is_last_redir = 1;
	}
	if (last_stdout)
	{
		redir = (t_redir *)last_stdout->content;
		redir->is_last_redir = 1;
	}
}

static int	handle_input_redirection(const char *filename, int is_last_redir)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return(-1);
	}
	if (is_last_redir)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (0);
}

static int	handle_output_redirection(const char *filename, int is_last_redir)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return(-1);
	}
	if (is_last_redir)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (0);
}

static int	handle_append_redirection(const char *filename, int is_last_redir)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return(-1);
	}
	if (is_last_redir)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (0);
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

static int handle_heredoc_redirection(const char *delimiter, t_mshell_data *data, int is_last_redir, int has_quotes)
{
	int		fd;
	char	*filename;
	
	filename = create_heredoc_filename();
	if (!filename)
	{
		perror("create_heredoc_filename");
		return (-1);
	}
	handle_heredoc(filename, delimiter, data, !has_quotes);
	if (is_last_redir)
	{
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			unlink(filename);
			free(filename);
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(fd);
			unlink(filename);
			free(filename);
			return (-1);
		}
		close(fd);
	}
	unlink(filename);
	free(filename);
	return (0);
}
