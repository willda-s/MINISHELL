/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:16 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/13 00:55:38 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

static void	unset_free(t_env *current)
{
	free(current->key);
	free(current->value);
	free(current);
}

int	builtin_unset(char *var, t_env *env)
{
	t_env	*current;
	t_env	*prev;

	current = env;
	prev = NULL;
	if (!var)
		return (0);
	if (current != NULL && ft_strcmp(current->key, var) == 0)
	{
		env = current->next;
		unset_free(current);
		return (EXIT_SUCCESS);
	}
	while (current != NULL)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			prev->next = current->next;
			unset_free(current);
			return (EXIT_SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
