/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc_signals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:43:18 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/11 20:33:38 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "libft.h"

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
