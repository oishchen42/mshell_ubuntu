/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:45:55 by oishchen          #+#    #+#             */
/*   Updated: 2025/08/13 20:00:06 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_export_argument(char *arg, t_mshell_data *data);
static char	*create_var(char *keyvalue, char *old_var);
static char	*ft_strdup_skip_plus(const char *s1);

int	minishell_export(char **args, t_mshell_data *data)
{
	int	status;
	int	exit_code;
	int	i;

	if (!args[1])
		return (minishell_env(data));
	exit_code = 0;
	i = 1;
	while (args[i])
	{
		status = process_export_argument(args[i], data);
		if (status != 0)
			exit_code = status;
		i++;
	}
	return (exit_code);
}

static int	process_export_argument(char *arg, t_mshell_data *data)
{
	if (arg[0] == '-')
	{
		ft_putendl_fd("minishell: export: options are not supported", 2);
		return (42);
	}
	if (!is_valid_key(arg, 1))
	{
		ft_putendl_fd("minishell: export: not valid in this context", 2);
		return (1);
	}
	if (!add_var(data, arg))
	{
		ft_putendl_fd("minishell: export: adding new variable failed", 2);
		return (42);
	}
	return (0);
}

int	add_var(t_mshell_data *data, char *keyvalue)
{
	int		key_idx;
	char	*new_var;

	key_idx = find_env(keyvalue, data->env);
	if (key_idx == -1)
		return (1);
	new_var = create_var(keyvalue, data->env[key_idx]);
	if (!new_var)
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
	else
		free(data->env[key_idx]);
	data->env[key_idx] = new_var;
	return (1);
}

static char	*create_var(char *keyvalue, char *old_var)
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
	if (!new_var)
	{
		ft_putendl_fd("error: create_var: malloc failed", 2);
		return (NULL);
	}
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
