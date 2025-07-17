/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:34:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/17 17:35:32 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "pipex.h"

# define FAIL 1
# define SUCCESS 0
# define CMD_NOT_FOUND -1

int				parse_builtin(char *cmd, t_mshell_data *data);
void			minishell_pwd(void);
void			minishell_cd(char **split);
int				minishell_echo(char **split);
int				minishell_export(char **split, t_mshell_data *data);
void			minishell_exit(t_mshell_data *data, int exit_code);
int				minishell_unset(char **split, t_mshell_data *data);

// cmd exe functions
void	print_arr(char *arr[]);
void	print_env(t_mshell_data *data);

// general_utils

/* finds necesarry environment variable in data->env,
	cases:
	1) no such env variable
		returns Last Index
	2) env variable is found
		returns env variable index
*/
int	find_env(char *keyvalue, t_mshell_data *data, int separator);

/*  realocates the data->env, while increasing it's size (x2);
	cases:
	1) failed allocation
			returns NULL;
*/
t_mshell_data	*ft_realloc(t_mshell_data *data, char **envp);

/* initialise data variable with by calculating the length of envp and calling ft_realloc
	cases:
	1) ft_realloc fails
		returns FAIL
	2) data was initialised
		returns SUCCESS
*/
int	init_data_env(t_mshell_data *data, char **envp);

/* checks the KEY for export and uset
	cases:
	1) KEY[0] is anything other than alpha || KEY[i] is anything other than alphanum or '_'
		returns 0 (false)
	2) KEY[0] is alpha and KEY[i] is alphanum || KEY[i] is '_'
		returns 1 (true)
*/
int	is_valid_key(char *key_value, int separator);

int should_add_to_history(const char *line);

//clean functions
void			free_split(char	**split);
void			free_pipex(t_pipex	*pipex);

#endif