/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:07:42 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/02 14:37:27 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	check_n_option(char *s)
{
	int	j;

	j = 0;
	if (s[j] != '-')
		return (false);
	j++;
	if (!s[j] || s[j] != 'n')
		return (false);
	while (s[j])
	{
		if (s[j] != 'n')
			return (false);
		j++;
	}
	return (true);
}

int	builtin_echo(t_exec *exec)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (exec->cmd[i] && check_n_option(exec->cmd[i]) == true)
	{
		i++;
		new_line = 0;
	}
	while (exec->cmd[i])
	{
		write(1, exec->cmd[i], ft_strlen(exec->cmd[i]));
		if (exec->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
