/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc_signals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:43:18 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/11 15:04:09 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "libft.h"
#include <readline/readline.h>

static void	handle_heredoc_sigint(int sig);

void	setup_heredoc_signals(void)
{
	setup_signal(SIGINT, handle_heredoc_sigint);
	setup_signal(SIGQUIT, SIG_IGN);
}

static void	handle_heredoc_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		exit(130);
	}
}
