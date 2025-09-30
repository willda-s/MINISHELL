/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 03:44:21 by willda-s          #+#    #+#             */
/*   Updated: 2025/10/01 00:23:40 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>
#include "ft_dprintf.h"

int	open_redir_in(t_exec *node, t_data *data, const char *filename)
{
	if (node->fd_in > 2)
		close(node->fd_in);
	node->fd_in = open(filename, O_RDONLY);
	if (node->fd_in == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n", filename);
		return (-1);
	}
	return (0);
}

int	open_redir_trunc(t_exec *node, t_data *data, const char *filename)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	node->fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node->fd_out == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", filename);
		return (-1);
	}
	return (0);
}

int	open_redir_append(t_exec *node, t_data *data, const char *filename)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	node->fd_out = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (node->fd_out == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", filename);
		return (-1);
	}
	return (0);
}

int	open_heredoc_in(t_exec *node, t_data *data, const char *filename)
{
	if (node->fd_in > 2)
		close(node->fd_in);
	node->fd_in = open(filename, O_RDONLY);
	if (node->fd_in == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n", filename);
		return (-1);
	}
	return (0);
}
