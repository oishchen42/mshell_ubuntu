/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:09:10 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/22 21:34:30 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

typedef enum quote_state
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_state;

// Redirection types
typedef enum redir_type
{
	REDIR_NONE,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_token
{
	char	*content;
	int		quote_state;
	int		redir_type;
	int		is_pipe;
}	t_token;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	char			*heredoc_delimiter;
}	t_redir;

typedef struct s_command
{
	char	**args;
	t_list	*redirections;
}	t_command;

t_token			*tokenize(const char *input);
int				check_quote_balance(const char *input);
t_command		*create_commands_from_tokens(t_token *tokens, int *n_cmds);

/* redirections */
int				add_redirection(t_list **redirections, t_token *tokens, int i);
t_redir_type	get_redir_type(const char *token);
void			print_redirections(t_list *redirections);
void			free_redir_content(void *content);

#endif
