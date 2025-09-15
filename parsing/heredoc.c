/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:57:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/15 19:59:04 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

void	handle_heredoc(t_data *data)
{
	t_exec	*tmp;
	t_redir	*redir;
	int		i;

	tmp = data->exec;
	redir = NULL;
	i = 0;
	while (tmp)
	{
		redir = tmp->redir;
		while (redir)
		{
			if (redir->delimiter)
			{
				open_heredoc_out(redir, data, i);
				i++;
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}
