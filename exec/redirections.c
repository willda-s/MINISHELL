/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:04:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/26 01:03:14 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "parsing.h"
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>

static int	open_redir_trunc(t_exec *node, t_data *data, char **filename)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	node->fd_out = open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node->fd_out == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", *filename);
		return (-1);
	}
	return (0);
}

static int	open_redir_append(t_exec *node, t_data *data, char **filename)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	node->fd_out = open(*filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (node->fd_out == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", *filename);
		return (-1);
	}
	return (0);
}

static int	open_redir_in(t_exec *node, t_data *data, char **filename)
{
	if (node->fd_in > 2)
		close(node->fd_in);
	node->fd_in = open(*filename, O_RDONLY);
	if (node->fd_in == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n", *filename);
		return (-1);
	}
	return (0);
}

static int	open_heredoc_in(t_exec *node, t_data *data, char **filename)
{
	if (node->fd_in > 2)
		close(node->fd_in);
	node->fd_in = open(*filename, O_RDONLY);
	unlink(*filename);
	if (node->fd_in == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n", *filename);
		return (-1);
	}
	return (0);
}

int	open_all_file(t_exec *node, t_data *data)
{
	t_redir	*tmp;
	char	*filename;

	tmp = node->redir;
	filename = NULL;
	while (tmp)
	{
		filename = ft_expand_word(data, tmp->filename);
		if (!filename)
			return (-1);
		if (tmp && tmp->token == REDIR_IN)
			data->errcode = open_redir_in(node, data, &filename);
		else if (tmp && tmp->token == REDIR_TRUNC)
			data->errcode = open_redir_trunc(node, data, &filename);
		else if (tmp && tmp->token == REDIR_APPEND)
			data->errcode = open_redir_append(node, data, &filename);
		else if (tmp && tmp->token == HEREDOC)
			data->errcode = open_heredoc_in(node, data, &filename);
		if (filename != NULL)
			free(filename);
		if (data->errcode < 0)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
