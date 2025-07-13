/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:23:56 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/13 21:43:22 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define ERROR_NO_CMD 10
# define ERROR_NO_FILE 20

# define READ_END 0
# define WRITE_END 1

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	**cmds;
	char	**envp;
	int		is_heredoc;
	int		n_cmds;
}	t_pipex;

/* special version of split for commands,
i.e checks for "" and '', additionally removes escape chars */
char	**ft_split_cmd(char const *s, char c);
void	fill_split(char **res, char const *s, char c);
int		count_splits_cmd(char const *s, char c);
int		find_next_split_cmd(char const *s, char *c);
void	suppress_mask_chars(char **str);

/* functions to initialize pipex struct */
t_pipex	*init_pipex(char *cmd, char *envp[]);

/* main pipex logic */
int		run_pipex(t_pipex *pipex_struct);
void	run_fork(int i, t_pipex *pipex_struct, int pipes[2][2]);
void	run_first_cmd(t_pipex *pipex_struct, int pipe[2]);
void	run_last_cmd(t_pipex *pipex_struct, int pipe[2]);
void	run_cmd(char *argv, char *envp[], int fd[]);

/* some helper functions to get environment vars and executable commands */
char	*find_path(char **env);
char	*get_exec_cmd(char *cmd, char **env, int *err_code);
char	*get_path_to(char *cmd, char *path);
void	exit_with_error(const char *msg, const char *obj, int exit_code);
void	exit_with_error_and_free(const char *msg, char **obj, int exit_code);

int		wait_for_child_procs(int pids[], int size);
void	close_pipe(int fd[2]);

#endif