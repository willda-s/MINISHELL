/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:07:51 by cafabre           #+#    #+#             */
/*   Updated: 2025/08/31 18:52:42 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (tmp->value)
		{
			write(1, tmp->key, ft_strlen(tmp->key));
			write(1, "=", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
