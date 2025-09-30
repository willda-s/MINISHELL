/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sigint_main_signals.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:23:52 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/11 20:34:45 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "libft.h"
#include <readline/readline.h>

static void	handle_sigint(int sig);

void	setup_main_signals(void)
{
	setup_signal(SIGINT, handle_sigint);
	setup_signal(SIGQUIT, SIG_IGN);
}

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
