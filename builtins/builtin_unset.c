/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:16 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/29 01:43:46 by cafabre          ###   ########.fr       */
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

int	builtin_unset(t_exec *exec, t_data *data)
{
	t_env	*current;
	t_env	*prev;
	size_t	i;
	bool	key_found;

	prev = NULL;
	if (!exec->cmd[1])
		return (0);
	i = 1;
	while (exec->cmd[i])
	{
		current = data->env;
		key_found = false;
		while (current != NULL && !key_found)
		{
			if (ft_strcmp(current->key, exec->cmd[i]) == 0)
			{
				if (prev == NULL)
					data->env = current->next;
				else
					prev->next = current->next;
				unset_free(current);
				key_found = true;
			}
			if (!key_found)
			{
				prev = current;
				current = current->next;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
