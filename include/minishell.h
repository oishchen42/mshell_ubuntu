/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:34:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/04 17:33:01 by nmikuka          ###   ########.fr       */
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
# include <signal.h>
# include "libft.h"
# include "tokenize.h"

# define FAIL 1
# define SUCCESS 0
# define CMD_NOT_FOUND -1

int		is_builtin(t_command cmd);

/* functions to initialize command struct */
int		parse_cmd(char *cmd, t_mshell_data *data);

/* main logic to run commands */
int		run_cmds(t_mshell_data *mshell_struct);
void	run_single_cmd(t_command cmd, t_mshell_data *mshell_struct);

/* some helper functions to get environment vars and executable commands */
char	*get_exec_cmd(char *cmd, char **env, int *err_code);
void	exit_with_error(const char *msg, const char *obj, int exit_code);
void	exit_with_error_and_free(const char *msg, char **obj, int exit_code);

void	handle_heredoc(char *heredoc_name, const char *delimiter);
void	handle_redirections(t_list *redirs);
int		wait_for_child_procs(int pids[], int size);

int		parse_builtin(t_command cmd, t_mshell_data *data);
int		minishell_pwd(void);
int		minishell_cd(char **split, t_mshell_data *data);
int		minishell_echo(char **split);
int		minishell_env(t_mshell_data *data);
int		minishell_export(char **split, t_mshell_data *data);
void	minishell_exit(char **cmd, t_mshell_data *data);
int		minishell_unset(char **split, t_mshell_data *data);

// signals
void	set_signals();

// cmd exe functions
// void	print_arr(char *arr[]);

// general_utils

/* finds necesarry environment variable in data->env,
	cases:
	1) no such env variable
		returns -1
	2) env variable is found
		returns env variable index
*/
int	find_env(char *keyvalue,  char **env);
int find_env_by_key(char *key, char **env, int key_len);

char	**ft_realloc(char **env, size_t *buffer_size);

/* initialise data variable with by calculating the length of envp
	and calling ft_realloc cases:
	1) ft_realloc fails
		returns FAIL
	2) data was initialised
		returns SUCCESS
*/
int		init_data_env(t_mshell_data *data, char **envp);

int		is_var_start_char(int c);
int		is_var_body_char(int c);
int		is_valid_key(char *key_value, int is_export);

int		should_add_to_history(const char *line);

void	free_env(t_mshell_data *data);

//clean functions
void	free_split(char	**split);

#endif