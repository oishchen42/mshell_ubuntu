/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:38:39 by oishchen          #+#    #+#             */
/*   Updated: 2025/08/14 16:46:36 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_unset_argument(char *arg, t_mshell_data *data);
static char	**remove_environment_variable(char *arg, t_mshell_data *data);

int	minishell_unset(char **args, t_mshell_data *data)
{
	int		i;
	int		status;
	int		exit_code;

	i = 1;
	exit_code = 0;
	while (args[i])
	{
		status = process_unset_argument(args[i], data);
		if (status)
			exit_code = status;
		i++;
	}
	return (exit_code);
}

static int	process_unset_argument(char *arg, t_mshell_data *data)
{
	if (arg[0] == '-')
	{
		ft_putendl_fd("minishell: unset: options are not supported", 2);
		return (42);
	}
	if (!is_valid_key(arg, 0))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	remove_environment_variable(arg, data);
	return (0);
}

static char	**remove_environment_variable(char *arg, t_mshell_data *data)
{
	size_t	i;
	int		key_idx;

	key_idx = find_env_by_key(arg, data->env, ft_strlen(arg));
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
