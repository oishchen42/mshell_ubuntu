/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:38:39 by oishchen          #+#    #+#             */
/*   Updated: 2025/08/04 17:50:57 by nmikuka          ###   ########.fr       */
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
	int		exit_code;

	i = 1;
	// if (!split[i])
	// {
	// 	ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
	// 	return (1);
	// }
	exit_code = 0;
	while (split[i])
	{
		if (is_valid_key(split[i], 0))
		{
			exit_code = 0;
			key_idx = find_env_by_key(split[i], data->env, ft_strlen(split[i]));
			if (key_idx >= 0 && (unsigned int)key_idx < data->env_len)
				data->env = delete_and_shift_env(data, key_idx);
		}
		else if (split[i][0] == '-')
		{
			exit_code = 2;
			ft_putendl_fd("minishell: export: invalid option, options not supported", 2);
		}
		else
		{
			exit_code = 1;
			ft_putendl_fd("unset: invalid parameter name", STDERR_FILENO);
		}
		i++;
	}
	return (exit_code);
}

int	is_var_start_char(int c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_var_body_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}