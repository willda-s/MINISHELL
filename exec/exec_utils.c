/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:47:42 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/12 19:32:55 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "signals.h"
#include <stdbool.h>
#include <errno.h>

bool	exec_builtins(t_exec *node, t_data *data)
{
	int	val;

	val = 1;
	if (!node->cmd || !(*node->cmd))
		return (-1);
	if (node->cmd && ft_strcmp(node->cmd[0], "echo") == 0)
		val = builtin_echo(node);
	else if (node->cmd && ft_strcmp(node->cmd[0], "exit") == 0)
	{
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
		val = builtin_unset(node->cmd[1], data->env);
	return (val);
}

int	wait_process(int nb_proc)
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

int	wait_one_process(int *flag)
{
	int	status;
	int	pid_w;
	int	exit_status;

	exit_status = 0;
	pid_w = wait(&status);
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
