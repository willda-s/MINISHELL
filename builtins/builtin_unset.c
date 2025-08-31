/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:16 by cafabre           #+#    #+#             */
/*   Updated: 2025/08/31 17:59:26 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_unset(char *var, t_env **env)
{
	t_env	*current;
	t_env	*prev;

	current = env;
	prev = NULL;
	if (current != NULL && strcmp(current->key, var) == 0)
	{
		*env = current->next;
		free(current->key);
		free(current->value);
		free(current);
		return (EXIT_SUCCESS);
	}
	while (current != NULL)
	{
		if (strcmp(current->key, var) == 0)
		{
			prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (EXIT_SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
