/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:09:10 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/28 12:18:49 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_BONUS_H
# define TOKENIZE_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

typedef enum {
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
} quote_state;

typedef struct s_token
{
	char	*content;
	int		quote_state;
	int		is_pipe;
}	t_token;

typedef struct s_command {
	char	**args;		// NULL-terminated array for execve
}	t_command;


typedef struct s_buffer
{
	char 	*str;
	size_t	size;
}	t_buffer;

char			*duplicate_buffer_size(char *buffer, size_t *buffer_size);

t_token	*tokenize(const char *input);
int		check_quote_balance(const char *input);
t_command		*create_commands_from_tokens(t_token *tokens, int *n_cmds, char **envp);
char			*expand_variables(const char *str, char **envp);

#endif
