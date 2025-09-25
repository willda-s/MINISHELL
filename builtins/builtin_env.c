/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:07:51 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/25 20:18:42 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static void	display_empty_export(t_env *tmp)
{
	write(1, "export ", 7);
	write(1, tmp->key, ft_strlen(tmp->key));
	if (ft_strlen(tmp->value) >= 1)
	{
		write(1, "=", 1);
		write(1, tmp->value, ft_strlen(tmp->value));
	}
	write(1, "\n", 1);
}

int	builtin_env(t_data *data, bool export)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (export == true)
			display_empty_export(tmp);
		else if (ft_strlen(tmp->value) >= 1)
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
