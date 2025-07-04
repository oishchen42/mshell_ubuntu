/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:02:33 by nmikuka           #+#    #+#             */
/*   Updated: 2025/07/04 12:33:38 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	char cmd[256];
	ssize_t bytes_read;

	(void) argc;
	(void) argv;
	(void) envp;
	bytes_read = 0;
	while (1)
	{
		write(STDOUT_FILENO, "minishell$ ", 12);
		bytes_read = read(STDIN_FILENO, cmd, sizeof(cmd) - 1);
		if (bytes_read > 0) {
				cmd[bytes_read] = '\0';
				printf("Read %zd bytes: %s", bytes_read, cmd);
			} else if (bytes_read == 0) {
				printf("EOF reached, no input read.\n");
			} else {
				perror("read error");
				return 1;
		}
	}

	return (0);
}
