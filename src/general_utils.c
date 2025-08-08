/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:41:03 by oishchen          #+#    #+#             */
/*   Updated: 2025/08/08 00:02:07 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env(char *keyvalue, char **env)
{
	size_t	i;
	int		key_len;
	char	*key_end;

	if (!keyvalue || !env)
		return (-1);
	key_end = ft_strnstr(keyvalue, "+=", ft_strlen(keyvalue));
	if (key_end)
		key_len = key_end - keyvalue;
	else
	{
		key_end = ft_strchr(keyvalue, '=');
		if (!key_end)
			return (-1);
		key_len = key_end - keyvalue;
	}
	i = find_env_by_key(keyvalue, env, key_len);
	return (i);
}

int	find_env_by_key(char *key, char **env, int key_len)
{
	size_t	i;

	if (!key)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	**ft_realloc(char **env, size_t *buffer_size)
{
	char	**new_env;
	size_t	new_buffer_size;
	size_t	i;

	new_buffer_size = *buffer_size * 2 + 1;
	new_env = malloc(sizeof(char *) * new_buffer_size);
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < *buffer_size)
	{
		new_env[i] = env[i];
		i++;
	}
	while (i < *buffer_size)
	{
		new_env[i] = NULL;
		i++;
	}
	free(env);
	*buffer_size = new_buffer_size;
	return (new_env);
}

int	is_valid_key(char *key_value, int is_export)
{
	int	i;

	i = 0;
	if (!is_var_start_char(key_value[i]))
		return (0);
	i++;
	while (key_value[i] && is_var_body_char(key_value[i]))
		i++;
	if (key_value[i] == '\0')
		return (1);
	if (is_export && (key_value[i] == '=' || ft_strncmp(&key_value[i], "+=", 2) == 0))
		return (1);
	return (0);
}