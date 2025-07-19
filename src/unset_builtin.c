/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:38:39 by oishchen          #+#    #+#             */
/*   Updated: 2025/07/19 20:02:58 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**shift_env(t_mshell_data *data, int key_idx)
{
	size_t	i;

	i = (unsigned int)key_idx;
	if (!data->env[key_idx])
		return (0);
	free(data->env[key_idx]);
	while(i < data->env_len - 1)
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		if (!data->env[i])
			return (ft_putendl_fd("Error: failed memory allocation in unset", 2), NULL);
		free(data->env[i + 1]);
		i++;
	}
	data->env_len--;
	return (data->env);
}

int	minishell_unset(char **split, t_mshell_data *data)
{
	size_t	i;
	int		key_idx;

	i = 1;
	if (!split[i])
		return (ft_putendl_fd("unset: not enough arguments", 2), EXIT_FAILURE);
	while (split[i])
	{
		if (is_valid_key(split[i], '\0') == 0)
			return (ft_putendl_fd("unset: invalid parameter name", 2), EXIT_FAILURE);
		key_idx = find_env(split[i], data, '\0');
		if (key_idx == -1 || (unsigned int)key_idx >= data->env_len)
			return (ft_putendl_fd("Error: KEY was not found", 2), EXIT_FAILURE);
		data->env = shift_env(data, key_idx);
		if (!data->env)
		{
			printf("NO DATA->ENV in unset\n");
			data->status = 0;
			return (ft_putendl_fd("Error: unset failed", 2), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
