/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:43:39 by zirael            #+#    #+#             */
/*   Updated: 2025/07/29 23:48:39 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_one_variable(const char *str, char **envp,
				t_buffer *buffer, size_t *j);
static int	ensure_buffer_capacity(t_buffer *buffer, size_t needed);

static int	is_var_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*expand_variables(const char *str, char **envp)
{
	t_buffer	result;
	int			i;
	size_t		j;

	result.size = ft_strlen(str) * 4;
	result.str = malloc(result.size + 1);
	if (!result.str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && is_var_char(str[i + 1]))
			i += expand_one_variable(&str[i], envp, &result, &j);
		else
		{
			if (!ensure_buffer_capacity(&result, j + 1))
				return (NULL);
			result.str[j++] = str[i++];
		}
	}
	result.str[j] = '\0';
	return (result.str);
}

static int	expand_one_variable(const char *str, char **envp,
				t_buffer *result, size_t *j)
{
	char	*var_name;
	char	*var_value;
	int		end;
	size_t	var_len;

	end = 1;
	while (is_var_char(str[end]))
		end++;
	var_name = ft_substr(str, 1, end - 1);
	if (!var_name)
		return (-1);
	var_value = ft_getenv(var_name, envp);
	if (var_value)
	{
		var_len = ft_strlen(var_value);
		if (!ensure_buffer_capacity(result, *j + var_len))
		{
			free(var_name);
			return (-1);
		}
		ft_strlcpy(result->str + *j, var_value, var_len + 1);
		*j += var_len;
	}
	free(var_name);
	return (end);
}

char	*ft_getenv(const char *name, char **envp)
{
	int		i;
	int		name_len;
	char	*env_entry;

	if (!name || !envp)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		env_entry = envp[i];
		if (ft_strncmp(env_entry, name, name_len) == 0
			&& env_entry[name_len] == '=')
			return (env_entry + name_len + 1);
		i++;
	}
	return (NULL);
}

static int	ensure_buffer_capacity(t_buffer *buffer, size_t needed)
{
	while (needed >= buffer->size)
	{
		buffer->str = duplicate_buffer_size(buffer->str, &buffer->size);
		if (!buffer->str)
			return (0);
	}
	return (1);
}
