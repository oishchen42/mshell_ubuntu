/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:02:33 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/07 09:18:20 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_promt(void);

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
	char	*cwd;
	char	*promt_start;
	char	*promt_end;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strjoin("minishell> ", ""));
	promt_start = ft_strjoin("minishell ", cwd);
	free(cwd);
	if (!promt_start)
		return (ft_strjoin("minishell> ", ""));
	promt_end = ft_strjoin(promt_start, "> ");
	if (!promt_end)
		return (ft_strjoin("minishell> ", ""));
	return (promt_end);
}

int	parse(char *cmd, char *envp[])
{
	char	**split;
	int		i;

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
	{
		chdir(split[1]);
	}
	else if (ft_strncmp(split[0], "pwd", 3) == 0)
	{
		minishell_pwd();
	}
	else if (ft_strncmp(split[0], "env", 3) == 0)
	{
		i = 0;
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
	else if (ft_strncmp(split[0], "echo", 4) == 0)
	{
		i = 1;
		while (split[i])
		{
			printf("%s ", split[i]);
			i++;
		}
		printf("\n");
	}
	free_split(split);
	return (1);
}

void	minishell_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}
