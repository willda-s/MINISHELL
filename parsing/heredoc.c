/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:57:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/11 19:04:45 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stddef.h>

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
