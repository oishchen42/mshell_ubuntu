/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:47:11 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/13 21:44:32 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **env)
{
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			return (&((*env)[5]));
		env++;
	}
	return (NULL);
}

char	*get_exec_cmd(char *cmd, char **env, int *err_code)
{
	char	*path;
	char	*cmd_ext;

	path = find_path(env);
	if (cmd && (cmd[0] == '.' || ft_strchr(cmd, '/') || path == NULL))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strjoin(cmd, "\0"));
		else
		{
			*err_code = ERROR_NO_FILE;
			return (NULL);
		}
	}
	cmd_ext = ft_strjoin("/", cmd);
	if (cmd_ext == NULL)
	{
		*err_code = ERROR_NO_CMD;
		return (NULL);
	}
	return (get_path_to(cmd_ext, path));
}

char	*get_path_to(char *cmd, char *path)
{
	char	**split_paths;
	char	*exec;
	int		i;

	split_paths = ft_split(path, ':');
	if (split_paths == NULL)
		return (NULL);
	i = 0;
	while (split_paths[i])
	{
		exec = ft_strjoin(split_paths[i], cmd);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free (cmd);
			free_split(split_paths);
			return (exec);
		}
		free(exec);
		i++;
	}
	free (cmd);
	free_split(split_paths);
	return (NULL);
}

void	exit_with_error(const char *msg, const char *obj, int exit_code)
{
	if (!obj)
		printf("pipex: %s\n", msg);
	else
		printf("pipex: %s: %s\n", obj, msg);
	exit (exit_code);
}

void	exit_with_error_and_free(const char *msg, char **obj, int exit_code)
{
	if (!obj)
		printf("pipex: %s\n", msg);
	else
	{
		printf("pipex: %s: %s\n", obj[0], msg);
		free_split(obj);
	}
	exit (exit_code);
}
