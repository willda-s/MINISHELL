/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:47:42 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/28 18:39:50 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "signals.h"
#include <errno.h>
#include <stdbool.h>

static int	exec_valid_builtins(t_exec *node, t_data *data, int val)
{
	if (node->cmd && ft_strcmp(node->cmd[0], "pwd") == 0)
		val = builtin_pwd();
	else if (node->cmd && ft_strcmp(node->cmd[0], "env") == 0)
		val = builtin_env(data, false);
	else if (node->cmd && ft_strcmp(node->cmd[0], "cd") == 0)
		val = builtin_cd(node, data);
	else if (node->cmd && ft_strcmp(node->cmd[0], "export") == 0)
		val = builtin_export(node, data);
	else if (node->cmd && ft_strcmp(node->cmd[0], "unset") == 0)
		val = builtin_unset(node->cmd[1], data);
	return (val);
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
		val = exec_valid_builtins(node, data, val);
	return (val);
}

void	print_wait_error(int flag)
{
	if (flag == 1)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (flag == 2)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
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
