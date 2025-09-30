/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:57:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 03:10:08 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

void	handle_heredoc(t_data *data)
{
	t_exec	*tmp;
	t_redir	*redir;

	tmp = data->exec;
	redir = NULL;
	while (tmp)
	{
		redir = tmp->redir;
		while (redir)
		{
			if (redir->delimiter)
			{
				open_heredoc_out(redir, data);
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}
