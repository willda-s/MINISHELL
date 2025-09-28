/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:47:42 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/28 22:54:18 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "signals.h"
#include <stdbool.h>
#include <sys/wait.h>

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
	else if (node->cmd && ft_strcmp(node->cmd[0], "pwd") == 0)
		val = builtin_pwd();
	else if (node->cmd && ft_strcmp(node->cmd[0], "env") == 0)
		val = builtin_env(data, false);
	else if (node->cmd && ft_strcmp(node->cmd[0], "cd") == 0)
		val = builtin_cd(node, data);
	else if (node->cmd && ft_strcmp(node->cmd[0], "export") == 0)
		val = builtin_export(node, data);
	else if (node->cmd && ft_strcmp(node->cmd[0], "unset") == 0)
		val = builtin_unset(node, data);
	return (val);
}

int	wait_process(t_data *data)
{
	int	n;
	int	ret;

	n = 0;
	data->errcode = 0;
	setup_parent_signals();
	ret = wait_one_process(&n, data->pid);
	if (ret != -1)
		data->errcode = ret;
	while (1)
	{
		ret = wait_one_process(&n, -1);
		if (ret == -1)
			break ;
	}
	print_wait_error(n);
	setup_main_signals();
	return (data->errcode);
}

int	wait_one_process(int *flag, pid_t pid)
{
	int		status;
	pid_t	pid_w;
	int		exit_status;

	exit_status = 0;
	pid_w = waitpid(pid, &status, 0);
	if (pid_w == -1)
		return (-1);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			*flag = 1;
		else if (WTERMSIG(status) == SIGQUIT)
			*flag = 2;
	}
	return (exit_status);
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
