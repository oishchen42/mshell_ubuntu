/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:57:21 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/14 16:46:45 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

int	update_quote_state(const char c, t_quote_state *quote_state)
{
	if (c == '"')
	{
		if (*quote_state == QUOTE_DOUBLE)
			*quote_state = QUOTE_NONE;
		else if (*quote_state == QUOTE_NONE)
			*quote_state = QUOTE_DOUBLE;
		else
			return (0);
		return (1);
	}
	if (c == '\'')
	{
		if (*quote_state == QUOTE_SINGLE)
			*quote_state = QUOTE_NONE;
		else if (*quote_state == QUOTE_NONE)
			*quote_state = QUOTE_SINGLE;
		else
			return (0);
		return (1);
	}
	return (0);
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

int	is_var_start_char(int c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_var_body_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}
