/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:00:43 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 01:04:50 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

char	*path_in_arg(t_exec *exec)
{
	char	*path;

	if (is_slash(exec) == 1)
	{
		if ((access(exec->cmd[0], F_OK) == -1)
			|| (access(exec->cmd[0], X_OK) == -1))
			return (NULL);
		else
		{
			path = ft_strdup(exec->cmd[0]);
			if (!path)
				return (NULL);
			return (path);
		}
	}
	return (NULL);
}

int	is_slash(t_exec *exec)
{
	int	j;

	j = 0;
	if (!exec->cmd || !exec->cmd[0])
		return (0);
	while (exec->cmd && exec->cmd[0][j])
	{
		if (exec->cmd[0][j] == '/')
			return (1);
		j++;
	}
	return (0);
}

int	find_path_line(t_data *data)
{
	int	i;

	i = 1;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	i = 0;
	return (-1);
}
