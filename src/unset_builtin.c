/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:38:39 by oishchen          #+#    #+#             */
/*   Updated: 2025/08/03 23:28:45 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**delete_and_shift_env(t_mshell_data *data, int key_idx)
{
	size_t	i;

	if (key_idx < 0 || (unsigned int) key_idx >= data->env_len
		|| !data->env[key_idx])
		return (NULL);
	free(data->env[key_idx]);
	i = (unsigned int)key_idx;
	while (i < data->env_len - 1)
	{
		data->env[i] = data->env[i + 1];
		i++;
	}
	data->env_len--;
	data->env[data->env_len] = NULL;
	return (data->env);
}

int	minishell_unset(char **split, t_mshell_data *data)
{
	size_t	i;
	int		key_idx;

	i = 1;
	if (!split[i])
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return (1);
	}
	while (split[i])
	{
		if (!is_valid_key(split[i]))
		{
			ft_putendl_fd("unset: invalid parameter name", STDERR_FILENO);
			return (1);
		}
		key_idx = find_env_by_key(split[i], data->env, ft_strlen(split[i]));
		if (key_idx == -1 || (unsigned int)key_idx >= data->env_len)
			return (0);
		data->env = delete_and_shift_env(data, key_idx);
		i++;
	}
	return (0);
}
