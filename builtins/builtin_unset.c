/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:16 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/30 01:24:04 by cafabre          ###   ########.fr       */
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

static void	remove_env_node(t_env *prev, t_env *current, t_data *data)
{
	if (prev == NULL)
		data->env = current->next;
	else
		prev->next = current->next;
	unset_free(current);
}

static void	move_to_next_node(t_env **prev, t_env **current)
{
	*prev = *current;
	*current = (*current)->next;
}

int	builtin_unset(t_exec *exec, t_data *data)
{
	t_env	*current;
	t_env	*prev;
	size_t	i;
	bool	key_found;

	prev = NULL;
	if (!exec->cmd[1])
		return (0);
	i = 0;
	while (exec->cmd[++i])
	{
		current = data->env;
		key_found = false;
		while (current != NULL && !key_found)
		{
			if (ft_strcmp(current->key, exec->cmd[i]) == 0)
			{
				remove_env_node(prev, current, data);
				key_found = true;
			}
			if (!key_found)
				move_to_next_node(&prev, &current);
		}
	}
	return (EXIT_SUCCESS);
}
