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
      
void	minishell_pwd(void);
void	minishell_cd(char **split);
int		minishell_echo(char **split);
int		minishell_export(char **split, char **env);

void	print_arr(char *arr[]);

//clean functions
void	free_split(char	**split);
void	free_pipex(t_pipex	*pipex);


#endif