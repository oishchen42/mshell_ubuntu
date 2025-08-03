/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:45:55 by oishchen          #+#    #+#             */
/*   Updated: 2025/08/03 21:10:17 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_env(t_mshell_data *data, char *keyvalue)
{
	int	key_idx;

	key_idx = find_env(keyvalue, data->env);
	if (key_idx == -1)
		return (0);
	if ((unsigned int)key_idx >= data->env_len)
	{
		data->env_len++;
		if (data->env_len > data->max_env_len)
		{
			data->env = ft_realloc(data->env, &data->max_env_len);
			if (!data->env)
				return (0);
		}
		data->env[data->env_len] = NULL;
	}
	data->env[key_idx] = ft_strdup(keyvalue);
	if (!data->env[key_idx])
	{
		free_env(data);
		return(0);
	}
	return (1);
}

int	minishell_export(char **split, t_mshell_data *data)
{
	int		i;
	int		exit_code;

	if (!split[1])
		return (minishell_env(data));
	exit_code = 0;
	i = 1;
	while (split[i])
	{
		if (is_valid_key(split[i]))
		{
			if (!add_env(data, split[i]))
			{
				exit_code = 1;
				ft_putendl_fd("ERROR: adding new variable failed", 2);
			}
		}
		else
		{
			exit_code = 1;
			ft_putendl_fd("export: not valid in this context", 2);
		}
		i++;
	}
	return (exit_code);
}
