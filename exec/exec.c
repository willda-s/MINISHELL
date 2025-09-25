/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:56:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/25 20:35:24 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "parsing.h"
#include "signals.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

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
	close_allfd_struct(data);
	free_all(data, true, data->errcode);
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
		{
			close_fd(tmp->next);
			dup_fd(tmp, data);
			exec_cmd(tmp, data);
		}
		else if (pid < 0)
		{
			setup_main_signals();
			free_all(data, true, errno);
		}
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
// le cas du : cat | ls
// je ferme l'ecriture du cat quand ls s'execute simultanement
