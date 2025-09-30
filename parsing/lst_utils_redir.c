/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:55:51 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 22:21:57 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static int	lstsize_redir(t_redir *redir);

int	add_back_redir(t_redir **redir)
{
	t_redir	*node;
	t_redir	*tmp;

	node = ft_calloc(1, sizeof(t_redir));
	if (!node)
		return (1);
	node->next = NULL;
	if (!*redir)
		*redir = node;
	else
	{
		tmp = ft_lstlast_redir(*redir);
		tmp->next = node;
	}
	return (0);
}

void	free_lst_redir(t_redir **redir)
{
	t_redir	*tmp;
	int		size;

	size = lstsize_redir(*redir);
	if (!(*redir))
		return ;
	while (size--)
	{
		tmp = (*redir)->next;
		if ((*redir)->filename)
			free((*redir)->filename);
		if ((*redir)->delimiter)
			free((*redir)->delimiter);
		free(*redir);
		*redir = tmp;
	}
}

t_redir	*ft_lstlast_redir(t_redir *redir)
{
	if (!redir)
		return (redir);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

static int	lstsize_redir(t_redir *redir)
{
	int	i;

	i = 1;
	if (!redir)
		return (0);
	if (!redir->next)
		return (1);
	while (redir->next)
	{
		redir = redir->next;
		i++;
	}
	return (i);
}
