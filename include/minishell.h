/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:34:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/28 21:33:25 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "tokenize.h"

# define FAIL 1
# define SUCCESS 0
# define CMD_NOT_FOUND -1

typedef struct s_mshell_data
{
	char		**env;
	size_t		max_env_len;
	size_t		env_len;
	t_command	*commands;
	int			n_cmds;
	int			status;
}	t_mshell_data;

int		is_builtin(t_command cmd);

/* functions to initialize command struct */
int		parse_cmd(char *cmd, t_mshell_data *data);

/* main logic to run commands */
int		run_pipex(t_mshell_data *mshell_struct);
void	run_cmd(t_command cmd, t_mshell_data *mshell_struct);

/* some helper functions to get environment vars and executable commands */
char	*get_exec_cmd(char *cmd, char **env, int *err_code);
void	exit_with_error(const char *msg, const char *obj, int exit_code);
void	exit_with_error_and_free(const char *msg, char **obj, int exit_code);

void	handle_heredoc(char *heredoc_name, const char *delimiter);
void	handle_redirections(t_list *redirs);
int		wait_for_child_procs(int pids[], int size);

int		parse_builtin(t_command cmd, t_mshell_data *data);
void	minishell_pwd(void);
void	minishell_cd(char **split);
int		minishell_echo(char **split);
void	minishell_env(t_mshell_data *data);
int		minishell_export(char **split, t_mshell_data *data);
void	minishell_exit(t_mshell_data *data, int exit_code);
int		minishell_unset(char **split, t_mshell_data *data);

// cmd exe functions
// void	print_arr(char *arr[]);

// general_utils

/* finds necesarry environment variable in data->env,
	cases:
	1) no such env variable
		returns Last Index
	2) env variable is found
		returns env variable index
*/
int		find_env(char *keyvalue, t_mshell_data *data, int separator);

/*  realocates the data->env, while increasing it's size (x2);
	cases:
	1) failed allocation
			returns NULL;
*/
t_mshell_data	*ft_realloc(t_mshell_data *data, char **envp);

/* initialise data variable with by calculating the length of envp
	and calling ft_realloc cases:
	1) ft_realloc fails
		returns FAIL
	2) data was initialised
		returns SUCCESS
*/
int		init_data_env(t_mshell_data *data, char **envp);

/* checks the KEY for export and uset
	cases:
	1) KEY[0] is anything other than alpha || KEY[i] is anything other
		than alphanum or '_'
		returns 0 (false)
	2) KEY[0] is alpha and KEY[i] is alphanum || KEY[i] is '_'
		returns 1 (true)
*/
int		is_valid_key(char *key_value, int separator);

int		should_add_to_history(const char *line);

void	free_env(t_mshell_data *data);

//clean functions
void	free_split(char	**split);

#endif