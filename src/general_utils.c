/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:41:03 by oishchen          #+#    #+#             */
/*   Updated: 2025/07/16 10:09:59 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief realocates the data->env while using data->env_len;
ALSO used at the beginning of the main to copy the envp to data->env
	@param data - a general struct which hold all environment variables(ev) and ev length;
	@param envp - almost always NULL except at the beginning of the main;
*/

int	find_env(char *keyvalue, t_mshell_data *data)
{
	size_t	i;
	char	*key;
	char	*equal;

	equal = ft_strchr(keyvalue, '=');
	if (equal)
	{
		key = ft_substr(keyvalue, 0, equal - keyvalue);
		if (!key)
			return (-1);
		i = 0;
		while (data->env[i] && i < data->env_len)
		{
			if (ft_strncmp(data->env[i], key, ft_strlen(key)) == 0)
				return (free(key), i);
			i++;
		}
		return (free(key), i);
	}
	return (-1);
}

t_mshell_data	*ft_realloc(t_mshell_data *data, char **envp)
{
	char	**new_env;
	size_t	i;
	size_t	new_env_len;

	new_env_len = (data->max_env_len * 2) + 1;
	new_env = malloc(sizeof(char *) * new_env_len);
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i != data->max_env_len)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
			return (ft_putstr_fd("Error: realloc was crushed", 2), free_split(new_env), NULL);
	}
	data->env_len = i;
	data->max_env_len = new_env_len;
	if (data->env)
		free_split(data->env);
	data->env = new_env;
	data->env[data->max_env_len - 1] = NULL;
	return (data);
}

int	init_data_env(t_mshell_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->env = NULL;
	data->max_env_len = i;
	data->env_len = i;
	data = ft_realloc(data, envp);
	if (data)
	{
		data->status = 1;
		return (EXIT_SUCCESS);
	}
	data->status = 0;
	return (EXIT_FAILURE);
}