/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:02:33 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/13 13:24:34 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../get_next_line/get_next_line.h"

// static char	*get_promt(void);
// static char	*get_curr_dir(void);
static void	process_user_input(char *user_input, t_mshell_data *data);
static int	process_single_command_line(char *cmd_line, t_mshell_data *data);
static int	validate_command_line(char *cmd);
static int	execute_command_line(char *cmd, t_mshell_data *data);

int	main(int argc, char *argv[], char *envp[])
{
	t_mshell_data	data;
	char			*user_input;

	(void) argc;
	(void) argv;
	if (init_data_env(&data, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data.exit_code = 0;
	set_signals();
	while (1)
	{
		if (isatty(fileno(stdin)))
			user_input = readline("Minishell-1.0$ ");
		else
		{
			char	*line;
			line = get_next_line(fileno(stdin));
			if (!line)
				user_input = NULL;
			else
			{
				user_input = ft_strtrim(line, "\n");
				free(line);
			}
		}
		if (!user_input)
		{
			free_split(data.env);
			rl_clear_history();
			exit(data.exit_code);
		}
		process_user_input(user_input, &data);
		free(user_input);
	}
	free_split(data.env);
	rl_clear_history();
	return (data.exit_code);
}

static void	process_user_input(char *user_input, t_mshell_data *data)
{
	char	**cmd_lines;
	int		i;

	cmd_lines = ft_split(user_input, '\n');
	if (!cmd_lines)
	{
		ft_putendl_fd("error: cmd_lines: malloc in ft_split failed", 42);
		return ;
	}
	i = 0;
	while (cmd_lines[i])
	{
		if (process_single_command_line(cmd_lines[i], data) == -1)
		{
			i++;
			continue ;
		}
		i++;
	}
	free_split(cmd_lines);
}

static int	process_single_command_line(char *cmd_line, t_mshell_data *data)
{
	char	*curr_cmd;

	add_history(cmd_line);
	curr_cmd = ft_strtrim(cmd_line, "\t\n ");
	if (!curr_cmd)
	{
		ft_putendl_fd("error: curr_cmd: malloc in ft_strtrim failed", 42);
		return (-1);
	}
	if (!validate_command_line(curr_cmd))
	{
		data->exit_code = 42;
		free(curr_cmd);
		return (-1);
	}
	if (execute_command_line(curr_cmd, data) == -1)
	{
		free(curr_cmd);
		return (-1);
	}
	free(curr_cmd);
	return (0);
}

static int	validate_command_line(char *cmd)
{
	if (!check_quote_balance(cmd))
	{
		ft_putendl_fd("minishell: error: unbalanced quotes", 2);
		return (0);
	}
	if (has_forbidden_chars(cmd))
	{
		ft_putendl_fd("minishell: error: \\, ; and ~ are not implemented", 2);
		return (0);
	}
	return (1);
}

static int	execute_command_line(char *cmd, t_mshell_data *data)
{
	parse_cmd(cmd, data);
	if (!data->commands)
		return (-1);
	data->exit_code = run_cmds(data);
	free_commands(data->commands, data->n_cmds);
	return (0);
}

// static char	*get_promt(void)
// {
// 	char	*curr_dir;
// 	char	*promt_start;
// 	char	*promt_end;

// 	curr_dir = get_curr_dir();
// 	if (!curr_dir)
// 		return (ft_strjoin("minishell> ", ""));
// 	promt_start = ft_strjoin("minishell ", curr_dir);
// 	free(curr_dir);
// 	if (!promt_start)
// 		return (ft_strjoin("minishell> ", ""));
// 	promt_end = ft_strjoin(promt_start, "> ");
// 	free(promt_start);
// 	if (!promt_end)
// 		return (ft_strjoin("minishell> ", ""));
// 	return (promt_end);
// }

// static char	*get_curr_dir(void)
// {
// 	char	*cwd;
// 	char	*curr_dir;
// 	char	**split;
// 	int		i;

// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 		return (NULL);
// 	split = ft_split(cwd, '/');
// 	free(cwd);
// 	if (!split || !split[0])
// 		return (NULL);
// 	i = 0;
// 	while (split[i])
// 		i++;
// 	curr_dir = ft_strjoin(split[i - 1], "");
// 	free_split(split);
// 	return (curr_dir);
// }
