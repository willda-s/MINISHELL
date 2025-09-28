/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 21:51:32 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/25 23:15:50 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "parsing.h"
#include "signals.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

static void	handle_command_not_found(t_exec *node, t_data *data)
{
	if (node->cmd[0] && node->cmd[0][0] != '\0')
	{
		ft_dprintf(2, "minishell: %s: command not found\n", node->cmd[0]);
		data->errcode = 127;
	}
	else
	{
		ft_dprintf(2, "minishell: : command not found\n");
		data->errcode = 127;
	}
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
				handle_command_not_found(node, data);
		}
	}
	close_allfd_struct(data);
	free_all(data, errno);
	exit(data->errcode);
}

void	handle_null_pid(t_exec *tmp, t_data *data)
{
	close_fd(tmp->next);
	dup_fd(tmp, data);
	exec_cmd(tmp, data);
}

void	handle_negative_pid(t_data *data)
{
	setup_main_signals();
	free_all(data, errno);
}
