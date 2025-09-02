/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:06 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/29 13:31:55 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
=======
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:06 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:08:30 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
>>>>>>> cam

static int	lstsize_env(t_env *envd)
{
	int	i;

	i = 1;
	if (!envd)
		return (0);
	if (!envd->next)
		return (1);
	while (envd->next)
	{
		envd = envd->next;
		i++;
	}
	return (i);
}

void	free_lst_env(t_env **envd, bool ext, int errcode)
{
	t_env	*tmp;
	int		size;

	size = lstsize_env(*envd);
	if (!(*envd))
		return ;
	while (size--)
	{
		tmp = (*envd)->next;
		if ((*envd)->key)
<<<<<<< HEAD
			free((*envd)->key);
		if ((*envd)->value)
=======
		{
			free((*envd)->key);
			(*envd)->key = NULL;
		}
		if ((*envd)->value)
		{
>>>>>>> cam
			free((*envd)->value);
			(*envd)->value = NULL;
		}
		free(*envd);
		*envd = tmp;
	}
	if (ext)
		exit(errcode);
}

t_env	*ft_lstlast_env(t_env *envd)
{
	if (!envd)
		return (envd);
	while (envd->next)
		envd = envd->next;
	return (envd);
}

int	add_back_env(t_env **envd)
{
	t_env	*node;
	t_env	*tmp;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (1);
	node->next = NULL;
	if (!*envd)
		*envd = node;
	else
	{
		tmp = ft_lstlast_env(*envd);
		tmp->next = node;
	}
	return (0);
}
