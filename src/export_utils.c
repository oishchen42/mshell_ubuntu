/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:45:55 by oishchen          #+#    #+#             */
/*   Updated: 2025/07/16 11:53:11 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mshell_data *add_env(t_mshell_data *data, char *keyvalue, int	key_idx)
{
	free(data->env[key_idx]);
	data->env[key_idx] = ft_strdup(keyvalue);
	if (!data->env[key_idx])
		data->status = 0;
	return (data);
}

static int	add_new_env(char *keyvalue, t_mshell_data *data)
{
	int	key_idx;

	key_idx = find_env(keyvalue, data);
	if (key_idx == -1)
		return (0);
	if ((unsigned int)key_idx < data->max_env_len)
		data = add_env(data, keyvalue, key_idx);
	else
	{
		data->env_len++;
		if (ft_realloc(data, data->env))
			data = add_env(data, keyvalue, key_idx);
		else
			data->status = 0;
	}
	if ((unsigned int)key_idx >= data->env_len)
		data->env_len++;
	if (data->status == 0)
		return (0);
	return (1);
}

static int	is_valid_export_key(char *key_value)
{
	int		i;

	i = 0;
	if (ft_isalpha(key_value[i]) || key_value[i++] == '_')
	{
		while (key_value[i] && (ft_isalnum(key_value[i]) || key_value[i] == '_'))
				i++;
		if (key_value[i] == '=')
			return (1);
	}
	return (0);
}

int	minishell_export(char **split, t_mshell_data *data)
{
	int		i;

	i = 1;
	while (split[i])
	{
		if (is_valid_export_key(split[i]))
		{
			if (!add_new_env(split[i], data))
			{
				data->status = 0;
				return (ft_putendl_fd("ERROR: split_key_value is aborted", 2), EXIT_FAILURE);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
} 