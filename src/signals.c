/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:55:15 by oishchen          #+#    #+#             */
/*   Updated: 2025/07/27 02:49:53 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_new_prompt(int signum)
{
	(void)signum;
	int	status;

	status = write(1, "\n", 1);
	if (status == 1 && RL_ISSTATE(RL_STATE_READCMD))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signals()
{
	struct sigaction	ft_sigint;
	struct sigaction	ft_sigquit;

	ft_bzero(&ft_sigint, sizeof(ft_sigint));
	ft_bzero(&ft_sigquit, sizeof(ft_sigquit));
	ft_sigint.sa_handler = print_new_prompt;
	ft_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ft_sigint, NULL);
	sigaction(SIGQUIT, &ft_sigquit, NULL);
}


// ctrl + \\ is a SIGQUIT
// ctrl + C is a SIGINT
// ctrl + d is an end of file EOF
