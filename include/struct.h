/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:47:52 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/31 19:44:09 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
	int		ends_with_space;
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

typedef struct s_buffer
{
	char	*str;
	size_t	size;
}	t_buffer;

typedef struct s_mshell_data
{
	char		**env;
	size_t		max_env_len;
	size_t		env_len;
	t_command	*commands;
	int			n_cmds;
	int			status;
	int			exit_code;
}	t_mshell_data;

#endif