/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:07:42 by cafabre           #+#    #+#             */
/*   Updated: 2025/08/31 14:11:51 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int builtin_echo(t_exec *exec)
{
    int     i;
    int     new_line;

    i = 1;
    new_line = 1;
    if (exec->cmd[1] && ft_strncmp(exec->cmd[1], "-n", 2) == 0)
    {
        i = 2;
        new_line = 0;
    }
    while (exec->cmd[i])
    {
        write(exec->fd_out, exec->cmd[i], ft_strlen(exec->cmd[i]));
        if (exec->cmd[i + 1])
            write(exec->fd_out, " ", 1);
        i++;
    }
    if (new_line)
        write(exec->fd_out, "\n", 1);
    return (EXIT_SUCCESS);
}
