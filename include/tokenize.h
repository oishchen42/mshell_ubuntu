/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:09:10 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/19 00:03:26 by nmikuka          ###   ########.fr       */
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

t_token	*tokenize(const char *input);
int		check_quote_balance(const char *input);
t_command *create_commands_from_tokens(t_token *tokens, int *n_cmds);

#endif
