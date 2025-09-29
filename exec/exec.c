/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:56:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 00:13:33 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "parsing.h"
#include "signals.h"
#include <errno.h>
#include <stdio.h>

static int	exec_loop(t_data *data, t_exec *prev);
static void	init_pipe(t_exec *node, t_data *data);
static void	exec_cmd(t_exec *node, t_data *data);

void	execc(t_data *data)
{
	t_exec	*prev;

	prev = NULL;
	data->pid = exec_loop(data, prev);
	g_signal_status = wait_process(data);
	data->errcode = g_signal_status;
}

static int	exec_loop(t_data *data, t_exec *prev)
{
	t_exec	*tmp;

	tmp = data->exec;
	data->pid = -1;
	while (tmp)
	{
		if (tmp->next)
			init_pipe(tmp, data);
		else if (!prev && is_builtins_exec(tmp))
		{
			handle_builtins_in_parent(tmp, data);
			return (-1);
		}
		data->pid = fork();
		if (data->pid == -1)
		{
			close_allfd_struct(data);
			return (-1);
		}
		if (data->pid == 0)
		{
			close_fd(tmp->next);
			data->errcode = dup_fd(tmp, data);
			if (data->errcode == -1)
			{
				if (tmp->fd_in != -1)
					close(tmp->fd_in);
				free_all(data, true, errno);
			}
			exec_cmd(tmp, data);
		}
		else if (data->pid < 0)
		{
			setup_main_signals();
			free_all(data, true, errno);
		}
		close_fd(tmp);
		prev = tmp;
		tmp = tmp->next;
	}
	return (data->pid);
}

static void	init_pipe(t_exec *node, t_data *data)
{
	int		fd[2];
	t_exec	*next;

	next = node->next;
	if (pipe(fd) == -1)
		free_all(data, true, errno);
	node->fd_out = fd[1];
	next->fd_in = fd[0];
}

static void	exec_cmd(t_exec *node, t_data *data)
{
	setup_child_signals();
	if (node->cmd)
	{
		if (exec_builtins(node, data, -1, -1))
		{
			node->path = path_in_arg(node);
			if (node->path == NULL)
				node->path = find_path(node, data);
			if (node->path != NULL)
			{
				execve(node->path, node->cmd, data->envp);
				perror("execve");
				data->errcode = 126;
			}
			else
			{
				if (node->cmd[0] && node->cmd[0][0] != '\0')
				{
					ft_dprintf(2, "minishell: %s: command not found\n",
							node->cmd[0]);
					data->errcode = 127;
				}
				else
				{
					ft_dprintf(2, "minishell: : command not found\n");
					data->errcode = 127;
				}
			}
		}
	}
	close_fd(node);
	close_allfd_struct(data);
	free_all(data, true, data->errcode);
}
