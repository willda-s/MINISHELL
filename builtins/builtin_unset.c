/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:16 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/24 01:51:20 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdlib.h>

static void	unset_free(t_env *current)
{
	free(current->key);
	free(current->value);
	free(current);
}

int	builtin_unset(char *var, t_data *data)
{
	t_env	*current;
	t_env	*prev;

	current = data->env;
	prev = NULL;
	if (!var)
		return (0);
	while (current != NULL)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			if (prev == NULL)
				data->env = current->next;
			else
				prev->next = current->next;
			unset_free(current);
			return (EXIT_SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
