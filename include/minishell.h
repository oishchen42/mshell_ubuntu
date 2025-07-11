/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:34:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/11 19:17:09 by oishchen         ###   ########.fr       */
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

void	minishell_pwd(void);
void	minishell_cd(char **split);
int		minishell_echo(char **split);

void	print_arr(char *arr[]);

// libft functions
void	free_split(char	**split);

//clean functions
void	free_split(char	**split);

int	minishell_export(char **split, char **env);

#endif