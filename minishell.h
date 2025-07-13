/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:34:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/13 13:52:17 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

int		parse(char *cmd, char *envp[]);
void	minishell_pwd(void);

// libft functions
int		ft_strncmp(const char *s1, const char *s2, int n);
char	**ft_split(char const *s, char c);
void	free_split(char	**split);

#endif