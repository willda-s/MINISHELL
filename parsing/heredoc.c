/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:57:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/08 00:15:02 by akarapkh         ###   ########.fr       */
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
