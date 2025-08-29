/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:33:45 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/29 13:33:44 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	suppr_line(t_exec *exec, int j)
{
	int	i;

	i = j + 1;
	free(exec->cmd[j]);
	while (exec->cmd && exec->cmd[i])
		exec->cmd[j++] = exec->cmd[i++];
	exec->cmd[j] = NULL;
}

void	remove_empty_line(t_data *data)
{
	t_exec	*tmp;
	int		i;

	tmp = data->exec;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd && tmp->cmd[i])
		{
			if (tmp->cmd && tmp->cmd[i] && ft_strncmp(tmp->cmd[i], " ",
					ft_strlen(tmp->cmd[i])) == 0)
				suppr_line(tmp, i);
			i++;
		}
		tmp = tmp->next;
	}
}
