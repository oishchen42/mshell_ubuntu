/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:57:10 by oishchen          #+#    #+#             */
/*   Updated: 2025/08/08 00:04:16 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_wds(t_mshell_data *data, char *path)
{
	char	*old_dir;
	char	*new_dir;

	// printf("data->old_dir: %s\n", data->old_dir);
	// printf("data->cur_dir: %s\n", data->cur_dir);
	old_dir = ft_strjoin("OLDPWD=", data->cur_dir);
	if (!old_dir)
		return (FALSE);
	new_dir = ft_strjoin("PWD=", path);
	if (!new_dir)
		return (free(old_dir), FALSE);
	if (!add_var(data, old_dir) || !add_var(data, new_dir))
		return (FALSE);
	free(old_dir);
	free(new_dir);
	free(data->old_dir);
	data->old_dir = ft_strdup(data->cur_dir);
	if (!data->old_dir)
		return (FALSE);
	free(data->cur_dir);
	data->cur_dir = ft_strdup(path);
	if (!data->cur_dir)
		return (free(data->old_dir), FALSE);
	// printf("------------------------------\n");
	// printf("data->old_dir: %s\n", data->old_dir);
	// printf("data->cur_dir: %s\n", data->cur_dir);
	// printf("------------------------------\n");
	return (TRUE);
}

int	exec_cd(t_mshell_data *data, char *path)
{
	char	cwd[4096];

	if (!getcwd(cwd, 4096))
	{
		ft_putendl_fd("cd: cannot access cwd", 2);
		return (FAIL);
	}
	if (chdir(path) != 0)
		return (FALSE);
	if (getcwd(cwd, 4096))
	{
		if (!update_wds(data, cwd))
		{
			ft_putendl_fd("cD: cannot access cwd", 2);
			return (FAIL);
		}
		else
			return (TRUE);
	}
	printf("we are not in TRUE\n");
	return (FALSE);
}

int	minishell_cd(char **split, t_mshell_data *data)
{
	int	status;

	// if (split[2] != NULL)
	// 	return (ft_putendl_fd("cd: to many args", 2), FAIL);
	if (!split[1] || ft_isspace(split[1][0]) || split[1][0] == '\0')
		status = exec_cd(data, data->home_dir);
	else if (ft_strncmp(split[1], "-", 2) == 0)
		status = exec_cd(data, data->old_dir);
	else
		status = exec_cd(data, split[1]);
	if (status == FALSE)
	{
		perror("cHdir");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}