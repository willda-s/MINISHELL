/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:56:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/12 16:55:44 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "parsing.h"
#include "signals.h"
#include <errno.h>
#include <stdlib.h>

static int	wait_process(int nb_proc)
{
	int	err;
	int	count;
	int	n;
	int	ret;

	err = 0;
	count = 0;
	n = 0;
	setup_parent_signals();
	while (count < nb_proc)
	{
		ret = wait_one_process(&n);
		if (ret == -1)
		{
			setup_main_signals();
			exit(errno);
		}
		err = ret;
		count++;
	}
	print_wait_error(n);
	setup_main_signals();
	return (err);
}

static void	exec_cmd(t_exec *node, t_data *data)
{
	setup_child_signals();
	if (node->cmd)
	{
		if (exec_builtins(node, data))
		{
			node->path = path_in_arg(node);
			if (node->path == NULL)
				node->path = find_path(node, data);
			if (node->path != NULL)
				execve(node->path, node->cmd, data->envp);
			ft_dprintf(2, "%s: command not found\n", node->cmd[0]);
		}
	}
	close_allfd_struct(data);
	free_all(data, errno);
}

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

static void	handle_fork(t_exec *tmp, t_data *data, t_exec *prev, int *i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup_fd(tmp, data);
		exec_cmd(tmp, data);
	}
	else if (pid < 0)
	{
		setup_main_signals();
		free_all(data, errno);
	}
	close_fd(tmp);
	(*i)++;
}

static void	exec_loop(int *i, t_data *data, t_exec *prev)
{
	t_exec	*tmp;

	tmp = data->exec;
	while (tmp)
	{
		if (tmp->next)
			init_pipe(tmp);
		else if (!prev && !exec_builtins(tmp, data))
			return ;
		handle_fork(tmp, data, prev, i);
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
	g_signal_status = wait_process(i);
	data->errcode = g_signal_status;
}

// le cas du : cat | ls
// je ferme l'ecriture du cat quand ls s'execute simultanement