/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:28:33 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/18 23:14:48 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "signals.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void wrapper_dup2(int oldfd, int newfd, t_data *data, int fd_other)
{
    if (dup2(oldfd, newfd) == -1)
    {
        if (fd_other != -1)
          close(fd_other);
        perror("dup2");
        free_all(data, errno);
    }
}

static void wrapper_dup(int oldfd, int *newfd, int fd_other, t_data *data)
{
    *newfd = dup(oldfd);
    if (*newfd == -1)
    {
        if (fd_other != -1)
            close(fd_other);
        perror("dup");
        free_all(data, errno);
    }
}

void handle_builtins_in_parent(t_exec *node, t_data *data)
{
	int fd_backup_in;
	int fd_backup_out;

    fd_backup_in = -1;
    fd_backup_out = -1;
	wrapper_dup(STDIN_FILENO, &fd_backup_in, fd_backup_out, data);
	wrapper_dup(STDOUT_FILENO, &fd_backup_out, fd_backup_in, data);
	dup_fd(node, data);
	exec_builtins(node, data, fd_backup_in, fd_backup_out);
    wrapper_dup2(fd_backup_in, STDIN_FILENO, data, fd_backup_out);
    wrapper_dup2(fd_backup_out, STDOUT_FILENO, data, fd_backup_in);
    close(fd_backup_in);
    close(fd_backup_out);
	close_fd(node);
	data->errcode = g_signal_status;
}