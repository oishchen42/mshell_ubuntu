/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:55:15 by oishchen          #+#    #+#             */
/*   Updated: 2025/07/23 02:33:03 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_new_prompt(int signum)
{
	(void)signum;
	int	status;

	status = write(1, "\n", 1);
	if (status == 1)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else
		ft_putendl_fd("Error: stdout is closed", 2);
}

void	set_signals()
{
	struct sigaction	ft_sigint;
	struct sigaction	ft_sigquit;

	ft_sigint.sa_handler = &print_new_prompt;
	ft_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ft_sigint, NULL);
	sigaction(SIGQUIT, &ft_sigquit, NULL);
}


// ctrl + \\ is a SIGQUIT
// ctrl + C is a SIGINT
// ctrl + d is an end of file EOF