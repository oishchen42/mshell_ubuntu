/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:02:33 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/06 09:10:32 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char *argv[], char *envp[])
{
	char *cmd;

	(void) argc;
	(void) argv;
	(void) envp;
	while (1)
	{
		cmd = readline("minishell> ");
		printf("%s \n", cmd);
	}
	return (0);
}
