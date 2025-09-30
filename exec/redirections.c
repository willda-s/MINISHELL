/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:04:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 03:47:03 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static void	wich_open(t_exec *node, char *filename, t_data *data, t_redir *tmp)
{
	if (tmp && tmp->token == REDIR_IN)
		data->errcode = open_redir_in(node, data, filename);
	else if (tmp && tmp->token == REDIR_TRUNC)
		data->errcode = open_redir_trunc(node, data, filename);
	else if (tmp && tmp->token == REDIR_APPEND)
		data->errcode = open_redir_append(node, data, filename);
	else if (tmp && tmp->token == HEREDOC)
	{
		data->errcode = open_heredoc_in(node, data, filename);
		unlink(filename);
	}
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
		wich_open(node, filename, data, tmp);
		free(filename);
		if (data->errcode < 0)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
