/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:18:53 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/25 14:21:09 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command cmd)
{
	if (!cmd.args || !cmd.args[0])
		return (0);
	if (ft_strncmp(cmd.args[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd.args[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd.args[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd.args[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd.args[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd.args[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd.args[0], "exit", 5) == 0)
		return (1);
	return (0);
}

int	parse_builtin(t_command cmd, t_mshell_data *data)
{
	if (!cmd.args)
		return (FAIL);
	if (ft_strncmp(cmd.args[0], "cd", 3) == 0)
		minishell_cd(cmd.args);
	else if (ft_strncmp(cmd.args[0], "pwd", 4) == 0)
		minishell_pwd();
	else if (ft_strncmp(cmd.args[0], "env", 4) == 0)
		print_env(data);
	else if (ft_strncmp(cmd.args[0], "echo", 5) == 0)
		minishell_echo(cmd.args);
	else if (ft_strncmp(cmd.args[0], "export", 7) == 0)
		minishell_export(cmd.args, data);
	else if (ft_strncmp(cmd.args[0], "unset", 6) == 0)
		minishell_unset(cmd.args, data);
	else if (ft_strncmp(cmd.args[0], "exit", 5) == 0)
		minishell_exit(data, 0);
	else
		return (CMD_NOT_FOUND);
	return (SUCCESS);
}
