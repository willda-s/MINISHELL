/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:13:24 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 00:19:37 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <bits/floatn-common.h>
#include <unistd.h>

void	close_allfd_struct(t_data *data)
{
	t_exec	*tmp;

	tmp = data->exec;
	while (tmp)
	{
		close_fd(tmp);
		tmp = tmp->next;
	}
}

void	close_last_fd(t_exec *node)
{
	if (node && node->fd_out != -1)
	{
		close(node->fd_out);
		node->fd_out = -1;
	}
}

void	close_first_fd(t_exec *node)
{
	if (node && node->fd_in != -1)
	{
		close(node->fd_in);
		node->fd_in = -1;
	}
}

void	close_fd(t_exec *node)
{
	close_first_fd(node);
	close_last_fd(node);
}

int	dup_fd(t_exec *node, t_data *data)
{
	int	i;

	i = open_all_file(node, data);
	if (i == -1)
		return (-1);
	if (node->fd_out != -1)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (-1);
		close(node->fd_out);
	}
	if (node->fd_in != -1)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(node->fd_in);
	}
	return (0);
}
