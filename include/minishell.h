/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:34:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/13 22:04:06 by nmikuka          ###   ########.fr       */
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

typedef struct s_mshell_data
{
	char	**env;
	size_t	env_len;
	int		status;
}	t_mshell_data;

void			minishell_pwd(void);
void			minishell_cd(char **split);
int				minishell_echo(char **split);
int				minishell_export(char **split, t_mshell_data *data);

// cmd exe functions
void	print_arr(char *arr[]);

// general_utils

/* finds necesarry environment variable in data->env,
	cases:
	1) no such env variable
		returns Last Index
	2) env variable is found
		returns env variable index
*/
int				find_env(char *key, t_mshell_data *data);

// realocates the data->env, while increasing it's size (x2);
	// cases:
	// 1) failed allocation
			// returns NULL;
t_mshell_data	*ft_realloc(t_mshell_data *data, char **envp);

/* initialise data variable with by calculating the length of envp and calling ft_realloc
	cases:
	1) ft_realloc fails
		returns FAIL
	2) data was initialised
		returns SUCCESS
*/
int	init_data_env(t_mshell_data *data, char **envp);

//clean functions
void			free_split(char	**split);
void	free_pipex(t_pipex	*pipex);

#endif