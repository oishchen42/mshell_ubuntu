/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:41:03 by oishchen          #+#    #+#             */
/*   Updated: 2025/07/14 17:52:05 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief realocates the data->env while using data->env_len;
ALSO used at the beginning of the main to copy the envp to data->env
	@param data - a general struct which hold all environment variables(ev) and ev length;
	@param envp - almost always NULL except at the beginning of the main;
*/

t_mshell_data	*ft_realloc(t_mshell_data *data, char **envp)
{
	char	**new_env;
	size_t	i;
	size_t	len;
	size_t	new_env_len;

	if (envp)
		data->env = envp;
	new_env_len = (data->env_len * 2) + 1;
	new_env = malloc(sizeof(char *) * new_env_len);
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i != data->env_len)
	{
		len = ft_strlen(data->env[i]);
		new_env[i] = malloc(len + 1);
		if (!new_env[i] || ft_strlcpy(new_env[i], data->env[i], (len + 1)) != len)
			return (ft_putendl_fd("problems with creation of new_env", 2), free_split(new_env), NULL); // in final ver delete ft_putendl
	}
	data->env_len = new_env_len;
	free_split(data->env);
	data->env = new_env;
	data->env[data->env_len - 1] = NULL;
	return (data);
}

int	find_env(char *key, t_mshell_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], key, ft_strlen(key)) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	init_data_env(t_mshell_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->env_len = i + 1;
	data = ft_realloc(data, envp);
	if (data)
	{
		data->status = 1;
		return (EXIT_SUCCESS);
	}
	data->status = 0;
	return (EXIT_FAILURE);
}
