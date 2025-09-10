/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:15:11 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/10 22:29:37 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal_status;

////////////////SIGNALS.C////////////////////////////

void							setup_main_signals(void);

void							setup_child_signals(void);

void							setup_parent_signals(void);

void							setup_heredoc_signals(void);

void							setup_signal(int sig, void (*handler)(int));

#endif