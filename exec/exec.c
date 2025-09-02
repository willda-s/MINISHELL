/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:56:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/02 18:41:59 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"
#include "parsing.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

static int	wait_process(int nb_proc)
{
	int	pid_w;
	int	status;
	int	err;
	int	count;

	err = 0;
	count = 0;
	while (count < nb_proc)
	{
		pid_w = wait(&status);
		if (pid_w == -1)
			exit(errno);
		if (WIFEXITED(status))
			err = WEXITSTATUS(status);
		count++;
	}
	return (err);
}

static void	exec_cmd(t_exec *node, t_data *data)
{
	if (node->cmd)
	{
		node->path = path_in_arg(node);
		if (node->path == NULL)
			node->path = find_path(node, data);
		if (node->path != NULL)
			execve(node->path, node->cmd, data->envp);
		ft_dprintf(2, "%s: command not found\n", node->cmd[0]);
	}
	close_allfd_struct(data);
	free_all(data, 127);
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

static void	exec_loop(int *i, t_data *data, t_exec *prev)
{
	t_exec	*tmp;
	pid_t	pid;

	tmp = data->exec;
	while (tmp)
	{
		if (tmp->next)
			init_pipe(tmp);
		pid = fork();
		if (pid == 0)
		{
			dup_fd(tmp, data);
			close_last_fd(prev);
			exec_cmd(tmp, data);
		}
		else if (pid < 0)
			free_all(data, errno);
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
	data->errcode = wait_process(i);
}
