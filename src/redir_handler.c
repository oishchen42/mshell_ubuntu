/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:32:40 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/22 23:41:51 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void handle_heredoc(char *heredoc_delimiter)
{
	int pipefd[2];
	pipe(pipefd);
	
	// Write heredoc content to pipe
	char *line = NULL;
	size_t len = 0;
	
	while (getline(&line, &len, stdin) != -1) {
		if (strncmp(line, heredoc_delimiter, strlen(heredoc_delimiter)) == 0 &&
			line[strlen(heredoc_delimiter)] == '\n') {
			break;  // Found delimiter
		}
		write(pipefd[1], line, strlen(line));
	}
	free(line);
	close(pipefd[1]);
	
	// Redirect stdin to read from pipe
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void handle_redirections(t_list *redirs) {
	t_list *current = redirs;
	
	while (current) {
		t_redir *redir = (t_redir *)current->content;
		int fd;
		
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
			handle_heredoc(redir->heredoc_delimiter);
		}
		current = current->next;
	}
}
