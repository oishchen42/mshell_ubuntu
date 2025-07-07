/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:34:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/07 23:47:48 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

void	minishell_pwd(void);
void	minishell_cd(char **split);
int		minishell_echo(char **split);

void	print_arr(char *arr[]);

// libft functions
int		ft_strncmp(const char *s1, const char *s2, int n);
char	**ft_split(char const *s, char c);
void	free_split(char	**split);
char	*ft_strjoin(char const *s1, char const *s2);

#endif