/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:04:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/15 18:57:03 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "parsing.h"
#include <fcntl.h>

static void	open_redir_trunc(t_exec *node, t_data *data, char *filename)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	node->fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node->fd_out == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", filename);
		free(filename);
		free_all(data, 1);
	}
}

static void	open_redir_append(t_exec *node, t_data *data, char *filename)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	node->fd_out = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (node->fd_out == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", filename);
		free(filename);
		free_all(data, 1);
	}
}

static void	open_redir_in(t_exec *node, t_data *data, char *filename)
{
	if (node->fd_in > 2)
		close(node->fd_in);
	node->fd_in = open(filename, O_RDONLY);
	if (node->fd_in == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n",
			filename);
		free(filename);
		free_all(data, 1);
	}
}

static void	open_heredoc_in(t_exec *node, t_data *data, char *filename)
{
	if (node->fd_in > 2)
		close(node->fd_in);
	node->fd_in = open(filename, O_RDONLY);
	if (node->fd_in == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n",
					filename);
		free(filename);
		free_all(data, 1);
	}
	unlink(filename);
}

void	open_all_file(t_exec *node, t_data *data)
{
	t_redir	*tmp;
	char *filename;

	tmp = node->redir;
	while (tmp)
	{
		filename = ft_expand_word(data, tmp->filename);
		if (!filename)
			return ;
		if (tmp && tmp->token == REDIR_IN)
			open_redir_in(node, data, filename);
		else if (tmp && tmp->token == REDIR_TRUNC)
			open_redir_trunc(node, data, filename);
		else if (tmp && tmp->token == REDIR_APPEND)
			open_redir_append(node, data, filename);
		else if (tmp && tmp->token == HEREDOC)
			open_heredoc_in(node, data, filename);
		free(filename);
		tmp = tmp->next;
	}
}
