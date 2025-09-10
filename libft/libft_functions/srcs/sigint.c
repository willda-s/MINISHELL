/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:23:52 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/10 22:30:36 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

volatile g_sig_atomic_t	gshell_exit_status;

void	setup_signal(int sig, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	if (handler == SIG_DFL || handler == SIG_IGN)
		sa.sa_flags = SA_RESTART;
	else
		sa.sa_flags = 0;
	if (sigaction(sig, &sa, NULL) != 0)
		ft_putstr_fd("minishell: signal setup failed\n", 2);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		gshell_exit_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_child_signals(void)
{
	setup_signal(SIGINT, SIG_DFL);
	setup_signal(SIGQUIT, SIG_DFL);
}

void	setup_parent_signals(void)
{
	setup_signal(SIGINT, SIG_IGN);
	setup_signal(SIGQUIT, SIG_IGN);
}

void	setup_heredoc_signals(void)
{
	setup_signal(SIGINT, SIG_DFL);
	setup_signal(SIGQUIT, SIG_IGN);
}

void	setup_main_signals(void)
{
	setup_signal(SIGINT, handle_sigint);
	setup_signal(SIGQUIT, SIG_IGN);
}