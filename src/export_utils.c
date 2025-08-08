/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:45:55 by oishchen          #+#    #+#             */
/*   Updated: 2025/08/08 00:13:52 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *create_var(char *keyvalue, char *old_var);
static char	*ft_strdup_skip_plus(const char *s1);

int	add_var(t_mshell_data *data, char *keyvalue)
{
	int		key_idx;
	char	*new_var;

	key_idx = find_env(keyvalue, data->env);
	if (key_idx == -1)
		return (1);
	new_var = create_var(keyvalue, data->env[key_idx]);
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
	else
		free(data->env[key_idx]);
	data->env[key_idx] = new_var;
	if (!data->env[key_idx])
	{
		free_split(data->env);
		return (0);
	}
	return (1);
}

static char *create_var(char *keyvalue, char *old_var)
{
	char	*new_var;
	int		i;

	i = 0;
	while (keyvalue[i] && is_var_body_char(keyvalue[i]))
		i++;
	if (keyvalue[i] == '=' || !old_var)
		new_var = ft_strdup_skip_plus(keyvalue);
	else
		new_var = ft_strjoin(old_var, &keyvalue[i + 2]);
	return (new_var);
}

static char	*ft_strdup_skip_plus(const char *s1)
{
	char	*dst;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(s1) + 1;
	dst = (char *)malloc(sizeof(char) * (size));
	if (dst == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (is_var_body_char(s1[j]))
		dst[i++] = s1[j++];
	if (s1[j] == '+')
		j++;
	while (s1[j])
		dst[i++] = s1[j++];
	dst[i] = '\0';
	return (dst);
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
		if (is_valid_key(split[i], 1))
		{
			exit_code = 0;
			if (!add_var(data, split[i]))
			{
				exit_code = 1;
				ft_putendl_fd("minishell: export: adding new variable failed", 2);
			}
		}
		else if (split[i][0] == '-')
		{
			exit_code = 2;
			ft_putendl_fd("minishell: export: invalid option, options not supported", 2);
		}
		else
		{
			exit_code = 1;
			ft_putendl_fd("minishell: export: not valid in this context", 2);
		}
		i++;
	}
	return (exit_code);
}