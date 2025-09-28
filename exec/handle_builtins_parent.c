/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:28:33 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/27 23:45:12 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "signals.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

static void	wrapper_dup(int oldfd, int *newfd, int fd_other, t_data *data);
static void	wrapper_dup2(int oldfd, int newfd, t_data *data, int fd_other);

void	handle_builtins_in_parent(t_exec *node, t_data *data)
{
	wrapper_dup(STDIN_FILENO, &data->fd_backup_in, data->fd_backup_out, data);
	wrapper_dup(STDOUT_FILENO, &data->fd_backup_out, data->fd_backup_in, data);
	data->errcode = dup_fd(node, data);
	if (data->errcode >= 0)
		exec_builtins(node, data, data->fd_backup_in, data->fd_backup_out);
	wrapper_dup2(data->fd_backup_in, STDIN_FILENO, data, data->fd_backup_out);
	wrapper_dup2(data->fd_backup_out, STDOUT_FILENO, data, data->fd_backup_in);
	close(data->fd_backup_in);
	close(data->fd_backup_out);
	close_fd(node);
	data->errcode = g_signal_status;
}

static void	wrapper_dup(int oldfd, int *newfd, int fd_other, t_data *data)
{
	*newfd = dup(oldfd);
	if (*newfd == -1)
	{
		if (fd_other != -1)
			close(fd_other);
		perror("dup");
		free_all(data, true, errno);
	}
}

static void	wrapper_dup2(int oldfd, int newfd, t_data *data, int fd_other)
{
	if (dup2(oldfd, newfd) == -1)
	{
		if (fd_other != -1)
			close(fd_other);
		perror("dup2");
		free_all(data, true, errno);
	}
}
