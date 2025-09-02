/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupfirstcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:13:24 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/28 15:50:45 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	ft_close(int *fd)
// {
// 	if (fd[0] != -1)
// 	{
// 		close(fd[0]);
// 		fd[0] = -1;
// 	}
// 	if (fd[1] != -1)
// 	{
// 		close(fd[1]);
// 		fd[1] = -1;
// 	}
// }

void	dup_cmd(t_exec *node, t_data *data)
{
	if (node->fd_out != -1)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		free_all(data, errno, "dup firstcmd fail\n", true);
	}
	else
	{
		if (dup2(1, STDOUT_FILENO) == -1)
		free_all(data, errno, "dup firstcmd fail\n", true);
	}
	if (node->fd_in != -1)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
		free_all(data, errno, "dup firstcmd fail\n", true);
	}
	else
	{
		if (dup2(0, STDIN_FILENO) == -1)
		free_all(data, errno, "dup firstcmd fail\n", true);
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