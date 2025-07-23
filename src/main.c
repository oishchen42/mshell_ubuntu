/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:02:33 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/23 16:26:04 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_promt(void);
static char	*get_curr_dir(void);

int	main(int argc, char *argv[], char *envp[])
{
	char			*cmd;
	char			*promt;
	int				status;
	t_mshell_data	data;

	(void) argc;
	(void) argv;
	(void) envp;
	if (init_data_env(&data, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (1)
	{
		promt = get_promt();
		cmd = readline(promt);
		if (promt)
			free(promt);
		if (!check_quote_balance(cmd))
		{
			write(STDERR_FILENO, "error: unbalanced quotes\n", 26);
			free(cmd);
			continue ;
		}
		data.pipex = init_pipex(cmd, envp);
		if (cmd)
		{
			if (should_add_to_history(cmd))
				add_history(cmd);
			free(cmd);
		}
		if (!data.pipex)
			break ;
		status = run_pipex(&data);
		free_pipex(data.pipex);
		if (!data.status)
		{
			printf("WE ARE IN DATA ERASER\n"); // DELETE
			free_split(data.env);
			break ;
		}
	}	
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	rl_clear_history();
	return (0);
}

static char	*get_promt(void)
{
	char	*curr_dir;
	char	*promt_start;
	char	*promt_end;

	curr_dir = get_curr_dir();
	if (!curr_dir)
		return (ft_strjoin("minishell> ", ""));
	promt_start = ft_strjoin("minishell ", curr_dir);
	free(curr_dir);
	if (!promt_start)
		return (ft_strjoin("minishell> ", ""));
	promt_end = ft_strjoin(promt_start, "> ");
	free(promt_start);
	if (!promt_end)
		return (ft_strjoin("minishell> ", ""));
	return (promt_end);
}

static char	*get_curr_dir(void)
{
	char	*cwd;
	char	*curr_dir;
	char	**split;
	int		i;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	split = ft_split(cwd, '/');
	free(cwd);
	if (!split || !split[0])
		return (NULL);
	i = 0;
	while (split[i])
		i++;
	curr_dir = ft_strjoin(split[i - 1], "");
	free_split(split);
	return (curr_dir);
}

int	parse_builtin(t_command cmd, t_mshell_data *data)
{
	// printf("Parsing ...%s...\n", cmd);
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
	else if (ft_strncmp(cmd.args[0], "exit", 5) == 0)
		minishell_exit(data, 0);
	else if (ft_strncmp(cmd.args[0], "unset", 5) == 0)
		minishell_unset(cmd.args, data);
	else
	{
		// free_split(data->env);
		return (CMD_NOT_FOUND);
	}
	// if (!data->status)
	// 	free_split(data->env);
	// free_split(split);
	return (SUCCESS);
}
