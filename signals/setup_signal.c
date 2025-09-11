/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:58:53 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/11 20:35:10 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signals.h>
#include "libft.h"

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
