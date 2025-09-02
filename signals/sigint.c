/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:23:52 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/02 15:54:36 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

static void	sigint_handler(int sig);

void	init_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	if (write(1, "\n", 1) == -1)
		return ;
	rl_on_new_line();
 	rl_replace_line("", 0);
 	rl_redisplay();
}

// void	setup_signal(int signo, void (*handler)(int))
// {
// 	struct sigaction	sa;

// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_handler = handler;
// 	if (handler == SIG_DFL || handler == SIG_IGN)
// 		sa.sa_flags = SA_RESTART;
// 	else
// 		sa.sa_flags = 0;
// 	if (sigaction(signo, &sa, NULL) != 0)
// 		ft_putstr_fd("minishell: signal setup failed\n", 2);
// }

// void	handle_sigint(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		variable_globale = 130;
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

// void	setup_child_signals(void)
// {
// 	setup_signal(SIGINT, SIG_DFL);
// 	setup_signal(SIGQUIT, SIG_DFL);
// }

// void	setup_parent_signals(void)
// {
// 	setup_signal(SIGINT, SIG_IGN);
// 	setup_signal(SIGQUIT, SIG_IGN);
// }

// void	setup_main_signals(void)
// {
// 	setup_signal(SIGINT, handle_sigint);
// 	setup_signal(SIGQUIT, SIG_IGN);
// }