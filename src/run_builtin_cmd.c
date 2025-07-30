/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:24:02 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/30 21:59:07 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (errno);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	minishell_cd(char **split, t_mshell_data *data)
{
	int	status;
	if (!split[1])
		status = chdir(ft_getenv("HOME", data->env));
	else
		status = chdir(split[1]);
	if (status == -1)
	{
		perror("chdir");
		return (1);
	}
	return (0);
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
		if (split[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	minishell_env(t_mshell_data *data)
{
	size_t	i;

	i = 0;
	if (!data->env)
		return (1);
	while (i < data->env_len)
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
}

static int is_numeric(char *str)
{
    int i;
    
    i = 0;
	if (!str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void	minishell_exit(char **cmd, t_mshell_data *data)
{
	if (cmd[1])
	{
		if (!is_numeric(cmd[1]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			data->exit_code = 255;
		}
		else if (cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			data->exit_code = 1;
		}
		else
			data->exit_code = (unsigned char)ft_atoi(cmd[1]);
	}
	if (isatty(STDIN_FILENO))
		printf("exit %i\n", data->exit_code);
	free_split(data->env);
	free_commands(data->commands, data->n_cmds);
	rl_clear_history();
	exit(data->exit_code);
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