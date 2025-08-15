/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:09:10 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/13 10:18:40 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdlib.h>
# include <stdio.h>
# include "struct.h"

# ifdef __linux__
#  define ERR_NUM_ARG_REQUIRED 2
# elif defined(__APPLE__)
#  define ERR_NUM_ARG_REQUIRED 255
# else
#  define ERR_NUM_ARG_REQUIRED 1
# endif
# define ERROR_NO_CMD 10
# define ERROR_NO_FILE 20

# define READ_END 0
# define WRITE_END 1

char			*duplicate_buffer_size(char *buffer, size_t *buffer_size);

t_token			*split_pipes_and_redirs(const char *input);
int				check_quote_balance(const char *input);
int				update_quote_state(const char c, t_quote_state *quote_state);
void			suppress_quotes(char *str, int *has_quotes);
t_command		*create_commands_from_tokens(t_token *tokens, int *n_cmds,
					t_mshell_data *data);
char			*expand_variables(const char *str, t_mshell_data *data);
char			*ft_getenv(const char *name, char **envp);

t_token			*split_args_by_space(t_token *tokens);
void			free_tokens(t_token *tokens);
void			free_commands(t_command *cmds, int n_cmds);

/* redirections */
int				add_redirection(t_list **redirections, t_token *tokens, int i,
					char *path);
t_redir_type	get_redir_type(const char *token);
void			print_redirections(t_list *redirections);
void			free_redir_content(void *content);

int				ft_isspace(char c);

#endif
