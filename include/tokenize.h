/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:09:10 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/31 19:26:00 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdlib.h>
# include <stdio.h>
# include "struct.h"

# define ERROR_NO_CMD 10
# define ERROR_NO_FILE 20

# define READ_END 0
# define WRITE_END 1

// Forward declare the struct instead of including minishell.h
typedef struct s_mshell_data t_mshell_data;

char			*duplicate_buffer_size(char *buffer, size_t *buffer_size);

t_token			*tokenize(const char *input);
int				check_quote_balance(const char *input);
int				skip_whitespace(const char *input, int i, int len);
t_command		*create_commands_from_tokens(t_token *tokens, int *n_cmds,
					t_mshell_data *data);
char			*expand_variables(const char *str, t_mshell_data *data);
char			*ft_getenv(const char *name, char **envp);
void			free_tokens(t_token *tokens);
void			free_commands(t_command *cmds, int n_cmds);

/* redirections */
int				add_redirection(t_list **redirections, t_token *tokens, int i);
t_redir_type	get_redir_type(const char *token);
void			print_redirections(t_list *redirections);
void			free_redir_content(void *content);

int				ft_isspace(char c);

#endif
