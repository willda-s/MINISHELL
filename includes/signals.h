/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:15:11 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/07 23:42:05 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_exit_status;

////////////////SIGNALS.C////////////////////////////

void							setup_main_signals(void);

void							setup_child_signals(void); 

void							setup_parent_signals(void);

void							setup_heredoc_signals(void);

void							setup_signal(int sig, void (*handler)(int));

#endif