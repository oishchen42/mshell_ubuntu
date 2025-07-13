/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:45:55 by oishchen          #+#    #+#             */
/*   Updated: 2025/07/13 23:42:01 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_mshell_data	*add_env(char *key, char *value, t_mshell_data *data)
// {
// 	int		env_idx;
// 	char	*new_env;

// 	env_idx = find_env(key, data);
// 	printf("env_idx %d\n", env_idx);
// 	if (!value)
// 		value = ft_strjoin(value, "");
// 	if (!value)
// 		return (NULL);
// 	new_env = ft_strjoin(key, value);
// 	if (!new_env)
// 		return (NULL);
// 	if (env_idx <= data->env_len)
// 	{
// 		free(data->env[env_idx]);
// 		data->env[env_idx] = malloc(ft_stlren(new_env) + 1);
// 		ft_strlcpy(data->env[env_idx], new_env, ft_strlen(new_env) + 1);
// 	}
// 	else
// 	{
// 		data->env = ft_realloc(data, NULL);
// 		data->env[env_idx] = malloc(ft_stlren(new_env) + 1);
// 		ft_strlcpy(data->env[env_idx], new_env, ft_strlen(new_env) + 1);
// 	}
// 	return (data);
// }

static t_mshell_data *add_env(t_mshell_data *data, char *keyvalue, int	key_idx)
{
	size_t	len;

	len = ft_strlen(keyvalue);
	free(data->env[key_idx]);
	data->env[key_idx] = malloc(len + 1);
	if (!data->env[key_idx])
		return (NULL);
	ft_strlcpy(data->env[key_idx], keyvalue, (len + 1));
	return (data);
}

static char	**add_new_env(char *keyvalue, char **temp, t_mshell_data *data)
{
	char	*equal;
	int		key_idx;

	equal = ft_strchr(keyvalue, '=');
	temp[0] = ft_substr(keyvalue, 0, equal - keyvalue);
	if (!temp[0])
		return (NULL);
	temp[1] = ft_substr(equal, 1, (unsigned int)ft_strlen(equal));
	if (!temp[1])
		return (free(temp[0]), NULL);
	temp[2] = NULL;
	key_idx = find_env(temp[0], data);

	printf("key_value[0] %s\n", temp[0]);
	printf("key_value[1] %s\n", temp[1]);
	
	if (data->env[key_idx])
		data = add_env(data, keyvalue, key_idx);
	else
	{
		if (ft_realloc(data, NULL))
			data = add_env(data, keyvalue, key_idx);
		else
			data->status = 0;
	}
	if (!data)
		return (free_split(temp), NULL);
	return (temp);
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
	char	**temp;

	temp = ft_split(split[3], '=');
	temp = malloc(sizeof(char *) * 3);
	i = 1;
	printf("WE ARE HER\n");
	if (split[i])
		printf("MY SPLIT: %s\n", split[i]);
	while (split[i])
	{
		if (is_valid_export_key(split[i]))
		{
			if (!add_new_env(split[i], temp, data))
			{
				data->status = 0;
				return (ft_putendl_fd("ERROR: split_key_value is aborted", 2), FAIL);
			}
			else
			{
				printf("SPLIT_KEY_VALUE success key[0] %s, key[1] %s\n", temp[0], temp[1]);
				free_split(temp);
			}
			// if (!env)
			// 	return (free_double_ptr(temp), 1);
			printf("WE ARE INSIDE IS_VALID_EXPORT\n");
		}
		else
			return (ft_putendl_fd("ERROR: <usage> export KEY=VALUE", 2), 1);
		i++;
	}
	// print_env(env);
	// printf("%s temp[0], %s temp[1]\n", temp[0], temp[1]);
	// free_double_ptr(split); // TODO?????
	// free_split(temp);
	// printf("No dobule FREE\n");
	
	return (0);
} 
