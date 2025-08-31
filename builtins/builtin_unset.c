/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:16 by cafabre           #+#    #+#             */
/*   Updated: 2025/08/31 14:08:17 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int  builtin_unset(char *var, t_env **env)
{
    t_env *current = *env;
    t_env *prev = NULL;
    
    if (current != NULL && strcmp(current->key, var) == 0)
    {
        *env = current->next;
        free(current->key);
        free(current->value);
        free(current);
        return (EXIT_SUCCESS);
    }
    while (current != NULL)
    {
        if (strcmp(current->key, var) == 0)
        {
            prev->next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return (EXIT_SUCCESS);
        }
        prev = current;
        current = current->next;
    }
    return (EXIT_SUCCESS);
}
