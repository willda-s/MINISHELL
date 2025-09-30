/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:47:42 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 03:47:36 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "signals.h"
#include <stdbool.h>
#include <sys/wait.h>
#include <errno.h>

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

bool	exec_builtins(t_exec *node, t_data *data, int fd_backup_in,
		int fd_backup_out)
{
	int	val;

	if (!node->cmd || !(*node->cmd))
		return (-1);
	val = 1;
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
		free_all(data, true, errno);
	node->fd_out = fd[1];
	next->fd_in = fd[0];
}
