/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:23:56 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/23 17:18:37 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "tokenize.h"

# define ERROR_NO_CMD 10
# define ERROR_NO_FILE 20

# define READ_END 0
# define WRITE_END 1

typedef struct s_pipex
{
	t_command	*commands;
	int			n_cmds;
}	t_pipex;

typedef struct s_mshell_data
{
	t_pipex	*pipex;
	char	**env;
	size_t	max_env_len;
	size_t	env_len;
	int		status;
}	t_mshell_data;

/* functions to initialize pipex struct */
t_pipex	*init_pipex(char *cmd, char *envp[]);

/* main pipex logic */
int		run_pipex(t_mshell_data *mshell_struct);
void	run_fork(int i, t_mshell_data *mshell_struct, int pipes[2][2]);
// void	run_first_cmd(t_mshell_data *mshell_struct, int pipe[2]);
// void	run_last_cmd(t_mshell_data *mshell_struct, int pipe[2]);
void	run_cmd(t_command cmd, t_mshell_data *mshell_struct);

/* some helper functions to get environment vars and executable commands */
char	*get_exec_cmd(char *cmd, char **env, int *err_code);
void	exit_with_error(const char *msg, const char *obj, int exit_code);
void	exit_with_error_and_free(const char *msg, char **obj, int exit_code);

void	handle_redirections(t_list *redirs);
int		wait_for_child_procs(int pids[], int size);
void	close_pipe(int fd[2]);

#endif