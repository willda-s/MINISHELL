/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:07:51 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/26 04:09:13 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

int	builtin_env(t_data *data, bool export)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (export == true)
		{
			write(1, "export ", 7);
			write(1, tmp->key, ft_strlen(tmp->key));
			if (tmp->value)
			{
				write(1, "=", 1);
				write(1, tmp->value, ft_strlen(tmp->value));
			}
			write(1, "\n", 1);
		}
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
