/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:07:51 by cafabre           #+#    #+#             */
/*   Updated: 2025/08/31 14:07:53 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int builtin_env(t_env *env)
{
    t_env *tmp = env;

    while (tmp)
    {
        if (tmp->value)
        {
            write(1, tmp->key, ft_strlen(tmp->key));
            write(1, "=", 1);
            write(1, tmp->value, ft_strlen(tmp->value));
            write(1, "\n", 1);
        }
        tmp = tmp->next;
    }
    return (0);
}
//fait : dupliquer l env + affichage
//a completer