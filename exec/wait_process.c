/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 03:00:24 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 03:03:09 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <sys/wait.h>
#include "signals.h"

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
