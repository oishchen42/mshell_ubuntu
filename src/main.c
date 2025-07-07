/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:02:33 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/07 17:25:22 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_promt(void);
static int	parse(char *cmd, char *envp[]);
static char	*get_curr_dir(void);

int	main(int argc, char *argv[], char *envp[])
{
	char	*cmd;
	char	*promt;

	(void) argc;
	(void) argv;
	(void) envp;
	while (1)
	{
		promt = get_promt();
		cmd = readline(promt);
		if (promt)
			free(promt);
		parse(cmd, envp);
		if (cmd)
			free(cmd);
	}
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

static int	parse(char *cmd, char *envp[])
{
	char	**split;

	// printf("Parsing ...%s...\n", cmd);
	if (!cmd)
		return (1);
	split = ft_split(cmd, ' ');
	if (!split || !split[0])
	{
		free_split(split);
		return (1);
	}
	if (ft_strncmp(split[0], "cd", 2) == 0)
		minishell_cd(split);
	else if (ft_strncmp(split[0], "pwd", 3) == 0)
		minishell_pwd();
	else if (ft_strncmp(split[0], "env", 3) == 0)
		print_arr(envp);
	else if (ft_strncmp(split[0], "echo", 4) == 0)
		minishell_echo(split);
	free_split(split);
	return (1);
}
