/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:55:03 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 22:46:59 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdio.h>

static int	lstsize_pars(t_pars *pars)
{
	int	i;

	i = 1;
	if (!pars)
		return (0);
	if (!pars->next)
		return (1);
	while (pars->next)
	{
		pars = pars->next;
		i++;
	}
	return (i);
}

void	free_lst_pars(t_pars **pars)
{
	t_pars	*tmp;
	int		size;

	size = lstsize_pars(*pars);
	if (!(*pars))
		return ;
	while (size--)
	{
		tmp = (*pars)->next;
		if ((*pars)->word)
			free((*pars)->word);
		free(*pars);
		*pars = tmp;
	}
}

t_pars	*ft_lstlast_pars(t_pars *pars)
{
	if (!pars)
		return (pars);
	while (pars->next)
		pars = pars->next;
	return (pars);
}

int	add_back_pars(t_pars **pars)
{
	t_pars	*node;
	t_pars	*tmp;

	node = ft_calloc(1, sizeof(t_pars));
	if (!node)
		return (1);
	node->next = NULL;
	if (!*pars)
		*pars = node;
	else
	{
		tmp = ft_lstlast_pars(*pars);
		tmp->next = node;
	}
	return (0);
}
