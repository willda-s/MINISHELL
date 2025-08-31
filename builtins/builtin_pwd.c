/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:12 by cafabre           #+#    #+#             */
/*   Updated: 2025/08/31 15:22:26 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int builtin_pwd(t_exec *exec)
{
    char    *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("pwd");
        return (EXIT_FAILURE);
    }
    write(1, cwd, ft_strlen(cwd));
    write(1, "\n", 1);
    free(cwd);
    return (EXIT_SUCCESS);
}
