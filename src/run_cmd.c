/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:24:02 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/13 23:41:05 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}

void	minishell_cd(char **split)
{
	if (!split[1] || ft_strncmp(split[1], "~", 1) == 0)
		printf("TODO: cd to $HOME\n");
	else
		chdir(split[1]);
}

int	minishell_echo(char **split)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (split[i] && ft_strncmp(split[i], "-n", 2) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (split[i])
	{
		printf("%s ", split[i]);
		i++;
	}
	if (newline)
		printf("\n");
	return (1);
}

void	print_arr(t_mshell_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->env_len)
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}
