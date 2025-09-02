/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:04:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/02 18:35:51 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"
#include "parsing.h"

static void	open_redir_trunc(t_exec *node, t_data *data, t_redir *tmp)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	node->fd_out = open(tmp->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node->fd_out == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", tmp->filename);
		free_all(data, 1);
	}
}

static void	open_redir_append(t_exec *node, t_data *data, t_redir *tmp)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	node->fd_out = open(tmp->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (node->fd_out == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", tmp->filename);
		free_all(data, 1);
	}
}

static void	open_redir_in(t_exec *node, t_data *data, t_redir *tmp)
{
	if (node->fd_in > 2)
		close(node->fd_in);
	node->fd_in = open(tmp->filename, O_RDONLY);
	if (node->fd_in == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n",
			tmp->filename);
		free_all(data, 1);
	}
}

static void	open_heredoc_in(t_exec *node, t_data *data, t_redir *tmp)
{
	if (node->fd_in > 2)
		close(node->fd_in);
	node->fd_in = open(tmp->filename, O_RDONLY);
	if (node->fd_in == -1)
	{
		close_allfd_struct(data);
		ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n",
			tmp->filename); // No SUCH FILE ... ?
		free_all(data, 1);
	}
	unlink(tmp->filename);
}

void	open_all_file(t_exec *node, t_data *data)
{
	t_redir	*tmp;

	tmp = node->redir;
	while (tmp)
	{
		if (tmp && tmp->token == REDIR_IN)
			open_redir_in(node, data, tmp);
		else if (tmp && tmp->token == REDIR_TRUNC)
			open_redir_trunc(node, data, tmp);
		else if (tmp && tmp->token == REDIR_APPEND)
			open_redir_append(node, data, tmp);
		else if (tmp && tmp->token == HEREDOC)
			open_heredoc_in(node, data, tmp);
		tmp = tmp->next;
	}
}
