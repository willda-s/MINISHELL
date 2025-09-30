/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:47:42 by willda-s          #+#    #+#             */
/*   Updated: 2025/10/01 00:25:30 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <errno.h>
#include <stdbool.h>
#include <sys/wait.h>

static void	wich_builtins(t_exec *node, t_data *data, int *val)
{
	if (node->cmd && ft_strcmp(node->cmd[0], "pwd") == 0)
		*val = builtin_pwd();
	else if (node->cmd && ft_strcmp(node->cmd[0], "env") == 0)
		*val = builtin_env(data, false);
	else if (node->cmd && ft_strcmp(node->cmd[0], "cd") == 0)
		*val = builtin_cd(node, data);
	else if (node->cmd && ft_strcmp(node->cmd[0], "export") == 0)
		*val = builtin_export(node, data);
	else if (node->cmd && ft_strcmp(node->cmd[0], "unset") == 0)
		*val = builtin_unset(node, data);
}

static void	close_and_free(t_data *data, int fd_backup_in, int fd_backup_out)
{
	if (data->pid == -1)
	{
		close(fd_backup_in);
		close(fd_backup_out);
	}
	free_all(data, true, 1);
}

bool	exec_builtins(t_exec *node, t_data *data, int fd_backup_in,
		int fd_backup_out)
{
	int	val;

	if (!node->cmd || !(*node->cmd))
		return (-1);
	val = -1;
	if (!node->cmd || !(*node->cmd))
		return (-1);
	if (node->cmd && ft_strcmp(node->cmd[0], "echo") == 0)
		val = builtin_echo(node);
	else if (node->cmd && ft_strcmp(node->cmd[0], "exit") == 0)
	{
		if (fd_backup_in != -1)
			close(fd_backup_in);
		if (fd_backup_out != -1)
			close(fd_backup_out);
		val = builtin_exit(node, data);
		val = 0;
	}
	else
		wich_builtins(node, data, &val);
	if (val == 2)
		close_and_free(data, fd_backup_in, fd_backup_out);
	return (val);
}

bool	is_builtins_exec(t_exec *node)
{
	if (!node->cmd || !(*node->cmd))
		return (false);
	if (ft_strcmp(node->cmd[0], "cd") == 0 || ft_strcmp(node->cmd[0],
			"echo") == 0 || ft_strcmp(node->cmd[0], "pwd") == 0
		|| ft_strcmp(node->cmd[0], "export") == 0 || ft_strcmp(node->cmd[0],
			"unset") == 0 || ft_strcmp(node->cmd[0], "env") == 0
		|| ft_strcmp(node->cmd[0], "exit") == 0)
		return (true);
	return (false);
}

void	init_pipe(t_exec *node, t_data *data)
{
	int		fd[2];
	t_exec	*next;

	next = node->next;
	if (pipe(fd) == -1)
	{
		close_allfd_struct(data);
		free_all(data, true, errno);
	}
	node->fd_out = fd[1];
	next->fd_in = fd[0];
}
