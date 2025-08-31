/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:02 by cafabre           #+#    #+#             */
/*   Updated: 2025/08/31 14:26:20 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int is_number(char *s)
{
    int i = 0;

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

long long ft_atoll(const char *str)
{
    long long result = 0;
    int sign = 1;

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

int builtin_exit(t_exec *exec, t_data *data)
{
   long long status;

   write(1, "exit\n", 5);
   if (exec->argc > 2)
   {
       write(1, "exit: too many arguments\n", 25);
       return (1);
   }
   if (exec->argc == 2)
   {
       if (!is_number(exec->argv[1]))
       {
           write(1, "exit: numeric argument required\n", 32);
           exit(2);
       }
       status = ft_atoll(exec->argv[1]);
       exit((unsigned char)status);
   }
   exit(data->errcode);
}
