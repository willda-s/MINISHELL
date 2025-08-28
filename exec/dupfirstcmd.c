/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupfirstcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:13:24 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/27 23:02:41 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_close(int *fd)
{
	if (fd[0] != -1)
	{
		close(fd[0]);
		fd[0] = -1;
	}
	if (fd[1] != -1)
	{
		close(fd[1]);
		fd[1] = -1;
	}
}
void	open_dup_close_firstcmd(t_data *data, int *fd)
{
	if (!fd)
		return;
	if (dup2(fd[1], 1) == -1)
		free_all(data, errno, "dup firstcmd fail\n", true);
	ft_close(fd);
}

void	open_dup_close_lastcmd(t_data *data, int *fd)
{
	if (!fd)
		return;
	if (dup2(fd[0], 0) == -1)
		free_all(data, errno, "dup lastcmd fail\n", true);
	ft_close(fd);
}