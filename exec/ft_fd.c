/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:13:24 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/02 16:56:27 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


void close_allfd_struct(t_data *data)
{
	t_exec *tmp = data->exec;
	while (tmp)
	{
		close_fd(tmp);
		tmp = tmp->next;
	}
}

void close_last_fd(t_exec *node)
{
	if (node && node->fd_out != -1)
	{
		close(node->fd_out);
		node->fd_out = -1;
	}
}

void close_first_fd(t_exec *node)
{
	if (node && node->fd_in != -1)
	{
		close(node->fd_in);
		node->fd_in = -1;
	}
}

void close_fd(t_exec *node)
{
	close_first_fd(node);
	close_last_fd(node);
}

void	dup_fd(t_exec *node, t_data *data)
{
	open_all_file(node, data);
	if (node->fd_out != -1)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		free_all(data, errno);
	}
	else
	{
		if (dup2(1, STDOUT_FILENO) == -1)
		free_all(data, errno);
	}
	if (node->fd_in != -1)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
		free_all(data, errno);
	}
	else
	{
		if (dup2(0, STDIN_FILENO) == -1)
		free_all(data, errno);
	}
}

// void	dup_lastcmd(t_exec *node, t_data *data)
// {
// 	if (node->fd_in != -1)
// 	{
// 		if (dup2(node->fd_in, 0) == -1)
// 			free_all(data, errno, "dup firstcmd fail\n", true);
// 	}
// }