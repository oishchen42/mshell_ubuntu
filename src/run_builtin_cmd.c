/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:24:02 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/28 21:34:29 by nmikuka          ###   ########.fr       */
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
	if (split[i] && ft_strncmp(split[i], "-n", 3) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (split[i])
	{
		printf("%s", split[i]);
		i++;
	}
	if (newline)
		printf("\n");
	return (1);
}

void	minishell_env(t_mshell_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->env_len)
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}

void	minishell_exit(t_mshell_data *data, int exit_code)
{
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	free_split(data->env);
	free_commands(data->commands, data->n_cmds);
	rl_clear_history();
	exit(exit_code);
}

// void	print_arr(char *arr[])
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		printf("%s\n", arr[i]);
// 		i++;
// 	}
// }