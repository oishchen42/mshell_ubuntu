/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:32:40 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/24 18:53:04 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_redirections(t_list *redirs)
{
	int		fd;
	t_list	*current;
	t_redir	*redir;
	
	current = redirs;
	while (current) {
		redir = (t_redir *)current->content;
		if (redir->type == REDIR_OUTPUT)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0) {
				perror("open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_INPUT)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd < 0) {
				perror("open");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_APPEND)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0) {
				perror("open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			handle_heredoc("_temp", redir->heredoc_delimiter);
			fd = open("_temp", O_RDONLY);
			if (fd < 0)
			{
				perror("open heredoc temp file");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			unlink("_temp");
		}
		current = current->next;
	}
}
