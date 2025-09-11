/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:06:14 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/11 16:06:39 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

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
