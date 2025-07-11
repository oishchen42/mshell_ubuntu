/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:45:55 by oishchen          #+#    #+#             */
/*   Updated: 2025/07/11 21:26:49 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_key_value(char *keyvalue, char **temp)
{
	char	*equal;

	equal = ft_strchr(keyvalue, '=');
	temp[0] = ft_substr(keyvalue, 0, equal - keyvalue);
	if (!temp[0])
		return (NULL);
	temp[1] = ft_substr(equal, 1, (unsigned int)ft_strlen(equal));
	if (!temp[1])
		return (free(temp[0]), NULL);
	temp[2] = NULL;
	printf("key_value[0] %s\n", temp[0]);
	printf("key_value[1] %s\n", temp[1]);
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

int	minishell_export(char **split, char **env)
{
	int		i;
	char	**temp;

	(void)env;
	temp = malloc(sizeof(char *) * 2);
	i = 1;
	printf("WE ARE HER\n");
	if (split[i])
		printf("MY SPLIT: %s\n", split[i]);
	while (split[i])
	{
		if (is_valid_export_key(split[i]))
		{
			if (!split_key_value(split[i], temp))
				return (ft_putendl_fd("ERROR: split_key_value is aborted", 2), 1);
			else
			{
				printf("SPLIT_KEY_VALUE success key[0] %s, key[1] %s\n", temp[0], temp[1]);
				free_split(temp);
			}
			// env = add_env(temp[0], temp[1], env);
			// if (!env)
			// 	return (free_double_ptr(temp), 1);
			// i++;
			printf("WE ARE INSIDE IS_VALID_EXPORT\n");
		}
		else
			return (ft_putendl_fd("ERROR: <usage> export KEY=VALUE", 2), 1);
	}
	// print_env(env);
	// printf("%s temp[0], %s temp[1]\n", temp[0], temp[1]);
	// free_double_ptr(split); // TODO?????
	// free_split(temp);
	// printf("No dobule FREE\n");
	
	return (0);
}
