/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:02:33 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/30 22:01:19 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../get_next_line/get_next_line.h"

static char	*get_promt(void);
static char	*get_curr_dir(void);

int	main(int argc, char *argv[], char *envp[])
{
	char			*cmd;
	char			*promt;
	// int				status;
	t_mshell_data	data;

	(void) argc;
	(void) argv;
	(void) envp;
	if (init_data_env(&data, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data.exit_code = 0;
	set_signals();
	while (1)
	{
		promt = get_promt();
		if (isatty(fileno(stdin)))
			cmd = readline(promt);
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			if (!line)
			{
				cmd = NULL;
				break ;
			}
			cmd = ft_strtrim(line, "\n");
			free(line);
		}
		if (promt)
			free(promt);
		if (!check_quote_balance(cmd))
		{
			write(STDERR_FILENO, "error: unbalanced quotes\n", 26);
			free(cmd);
			continue ;
		}
		if (should_add_to_history(cmd))
			add_history(cmd);
		parse_cmd(cmd, &data);
		if (cmd)
			free(cmd);
		if (!data.commands)
			break ;
		run_cmds(&data);
		free_commands(data.commands, data.n_cmds);
		// if (!data.status)
		// {
		// 	printf("WE ARE IN DATA ERASER\n"); // DELETE
		// 	free_split(data.env);
		// 	break ;
		// }
	}
	// if (WIFEXITED(status))
	// 	return (WEXITSTATUS(status));
	rl_clear_history();
	return (data.exit_code);
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
