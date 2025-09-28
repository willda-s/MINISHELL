/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:56:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/25 23:17:05 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "parsing.h"
#include "signals.h"
#include <errno.h>
#include <stdlib.h>

static void	init_pipe(t_exec *node)
{
	int		fd[2];
	t_exec	*next;

	next = node->next;
	if (pipe(fd) == -1)
		exit(errno);
	node->fd_out = fd[1];
	next->fd_in = fd[0];
}

static void	exec_loop(int *i, t_data *data, t_exec *prev)
{
	t_exec	*tmp;
	int		pid;

	tmp = data->exec;
	while (tmp)
	{
		if (tmp->next)
			init_pipe(tmp);
		else if (!prev && is_builtins_exec(tmp))
		{
			handle_builtins_in_parent(tmp, data);
			return ;
		}
		pid = fork();
		if (pid == 0)
			handle_null_pid(tmp, data);
		else if (pid < 0)
			handle_negative_pid(data);
		close_fd(tmp);
		(*i)++;
		prev = tmp;
		tmp = tmp->next;
	}
}

void	execc(t_data *data)
{
	t_exec	*prev;
	int		i;

	prev = NULL;
	i = 0;
	exec_loop(&i, data, prev);
	g_signal_status = wait_process(i, data);
	data->errcode = g_signal_status;
}
