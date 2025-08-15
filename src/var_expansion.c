/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:43:39 by zirael            #+#    #+#             */
/*   Updated: 2025/08/14 17:31:39 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_expansion(const char *str, t_mshell_data *data,
				t_buffer *result, t_quote_state quote_state);
static int	expand_single_variable(const char *str, char **envp,
				t_buffer *buffer);
static int	expand_exit_code(int exit_code, t_buffer *result);
static int	ensure_buffer_capacity(t_buffer *buffer, size_t needed);

char	*expand_variables(const char *str, t_mshell_data *data)
{
	t_buffer		result;
	int				i;
	int				chars_copied;
	t_quote_state	quote_state;

	result.size = ft_strlen(str) * 4;
	result.str = ft_calloc(result.size + 1, sizeof(char));
	if (!result.str)
		return (NULL);
	result.curr_pos = 0;
	i = 0;
	quote_state = QUOTE_NONE;
	while (str[i])
	{
		update_quote_state(str[i], &quote_state);
		chars_copied = handle_expansion(&str[i], data, &result, quote_state);
		if (chars_copied == 0)
		{
			ft_putendl_fd("expand_vars: memory allocation failed", 2);
			return (result.str);
		}
		i += chars_copied;
	}
	result.str[result.curr_pos] = '\0';
	return (result.str);
}

static int	handle_expansion(const char *str, t_mshell_data *data,
				t_buffer *result, t_quote_state quote_state)
{
	int	i;

	i = 0;
	if (quote_state != QUOTE_SINGLE
		&& str[i] == '$' && str[i + 1] && is_var_start_char(str[i + 1]))
		return (expand_single_variable(str, data->env, result));
	if (quote_state != QUOTE_SINGLE && str[i] == '$' && str[i + 1] == '?')
		return (expand_exit_code(data->exit_code, result));
	if (quote_state == QUOTE_NONE && str[i] == '$' && (str[i + 1] == '"'
			|| str[i + 1] == '\''))
		return (1);
	else
	{
		if (!ensure_buffer_capacity(result, result->curr_pos + 1))
			return (0);
		result->str[result->curr_pos++] = str[i];
		return (1);
	}
	return (0);
}

static int	expand_exit_code(int exit_code, t_buffer *result)
{
	char	*status_str;
	int		var_len;

	status_str = ft_itoa(exit_code);
	var_len = ft_strlen(status_str);
	if (!ensure_buffer_capacity(result, result->curr_pos + var_len))
	{
		free(status_str);
		return (0);
	}
	ft_strlcpy(result->str + result->curr_pos, status_str, var_len + 1);
	free(status_str);
	result->curr_pos += var_len;
	return (2);
}

static int	expand_single_variable(const char *str, char **envp,
				t_buffer *result)
{
	char	*var_name;
	char	*var_value;
	int		end;
	size_t	var_len;

	end = 1;
	while (is_var_body_char(str[end]))
		end++;
	var_name = ft_substr(str, 1, end - 1);
	if (!var_name)
		return (0);
	var_value = ft_getenv(var_name, envp);
	if (var_value)
	{
		var_len = ft_strlen(var_value);
		if (!ensure_buffer_capacity(result, result->curr_pos + var_len))
		{
			free(var_name);
			return (0);
		}
		ft_strlcpy(result->str + result->curr_pos, var_value, var_len + 1);
		result->curr_pos += var_len;
	}
	free(var_name);
	return (end);
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
