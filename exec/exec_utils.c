/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 00:34:23 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/08 00:41:05 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int	wait_one_process(int *n)
{
	int	status;
	int	pid_w;
	int	err;

	err = 0;
	pid_w = wait(&status);
	if (pid_w == -1)
		return (-1);
	if (WIFEXITED(status))
		err = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		err = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			*n = 1;
		else if (WTERMSIG(status) == SIGQUIT)
			*n = 2;
	}
	return (err);
}

void	print_wait_error(int n)
{
	if (n == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (n == 2)
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}
