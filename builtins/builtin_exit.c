/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:02 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/30 03:56:18 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "builtins.h"
#include <stdlib.h>
#include <unistd.h>

static int	is_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

static void	free_exit(t_data *data, int errcode)
{
	close_allfd_struct(data);
	free_all(data, true, errcode);
}

int	builtin_exit(t_exec *exec, t_data *data)
{
	long long	status;
	int			argc;

	argc = 0;
	while (exec->cmd[argc])
		argc++;
	write(1, "exit", 5);
	if (argc > 2)
	{
		write(1, ": too many arguments\n", 21);
		return (EXIT_FAILURE);
	}
	if (argc == 2)
	{
		if (!is_number(exec->cmd[1]))
		{
			write(1, ": numeric argument required", 28);
			free_exit(data, 2);
		}
		status = (unsigned char)(ft_atoll(exec->cmd[1]));
		free_exit(data, status);
	}
	write(1, "\n", 1);
	free_exit(data, data->errcode);
	return (0);
}
