/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_simple_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:24:02 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/13 23:39:20 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd_variable(t_mshell_data *data);
static int	is_new_line_option(char *str);
static int	is_numeric(char *str);

int	minishell_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putendl_fd("minishell: pwd: getcwd failed", 2);
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}

int	minishell_cd(char **split, t_mshell_data *data)
{
	int		status;

	if (!split[1])
		status = chdir(ft_getenv("HOME", data->env));
	else
		status = chdir(split[1]);
	if (status == -1)
	{
		ft_putendl_fd("minishell: cd: chdir failed", 2);
		return (1);
	}
	return (update_pwd_variable(data));
}

static int	update_pwd_variable(t_mshell_data *data)
{
	char	*current_dir;
	char	*pwd_variable;
	int		result;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		ft_putendl_fd("minishell: cd: getcwd failed", 2);
		return (1);
	}
	pwd_variable = ft_strjoin("PWD=", current_dir);
	free(current_dir);
	if (!pwd_variable)
	{
		ft_putendl_fd("minishell: cd: memory allocation failed", 2);
		return (42);
	}
	result = add_var(data, pwd_variable);
	free(pwd_variable);
	if (!result)
	{
		ft_putendl_fd("minishell: cd: failed to update PWD variable", 2);
		return (42);
	}
	return (0);
}

int	minishell_echo(char **split)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (split[i] && is_new_line_option(split[i]))
	{
		newline = 0;
		i++;
	}
	while (split[i])
	{
		ft_putstr_fd(split[i], STDOUT_FILENO);
		if (split[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

static int	is_new_line_option(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0' && i >= 2)
		return (1);
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

void	minishell_exit(char **cmd, t_mshell_data *data)
{
	if (cmd[1])
	{
		if (!is_numeric(cmd[1]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			data->exit_code = ERR_NUM_ARG_REQUIRED;
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

static int	is_numeric(char *str)
{
	int	i;

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
