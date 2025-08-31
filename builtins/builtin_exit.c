/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:02 by cafabre           #+#    #+#             */
/*   Updated: 2025/08/31 17:57:19 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_number(char *s)
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

long long	ft_atoll(const char *str)
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

int	builtin_exit(t_exec *exec, t_data *data)
{
	long long	status;
	int			argc;

	argc = 0;
	while (exec->cmd[argc])
		argc++;
	write(1, "exit\n", 5);
	if (argc > 2)
	{
		write(1, "exit: too many arguments\n", 25);
		return (EXIT_FAILURE);
	}
	if (argc == 2)
	{
		if (!is_number(exec->cmd[1]))
		{
			write(1, "exit: numeric argument required\n", 32);
			exit(2);
		}
		status = ft_atoll(exec->cmd[1]);
		exit((unsigned char)status);
	}
	exit(data->errcode);
}
