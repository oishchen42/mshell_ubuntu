/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mshell_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:59:08 by oishchen          #+#    #+#             */
/*   Updated: 2025/08/08 00:06:21 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cpy_env(t_mshell_data *data, char **envp)
{
	size_t	i;

	i = 0;
	while (i < data->env_len)
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
		{
			free_split(data->env);
			return (FALSE);
		}
		i++;
	}
	data->env[i] = NULL;
	return (TRUE);
}

static int	set_pwds(t_mshell_data *data)
{
	data->old_dir = ft_strdup(ft_getenv("OLDPWD", data->env));
	if (!data->old_dir)
	{
		ft_putendl_fd("bash: cd: OLDPWD not set", 2);
		return (TRUE);
	}
	data->cur_dir = ft_strdup(ft_getenv("PWD", data->env));
	if (!data->cur_dir)
	{
		ft_putendl_fd("bash: cd: OLDPWD not set", 2);
		return (FALSE);
	}
	data->home_dir = ft_strdup(ft_getenv("HOME", data->env));
	if (!data->home_dir)
	{
		ft_putendl_fd("bash: cd: HOME not set", 2);
		return (FALSE);
	}
	return (TRUE);
}

void 	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}

int	init_data_env(t_mshell_data *data, char **envp)
{
	data->env_len = 0;
	while (envp[data->env_len])
		data->env_len++;
	data->max_env_len = data->env_len + 1;
	data->env = malloc(sizeof(char *) * data->max_env_len);
	if (!data->env)
		return (EXIT_FAILURE);
	if (!cpy_env(data, envp))
		return (EXIT_FAILURE);
	// print_env(data->env);
	if (!set_pwds(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}