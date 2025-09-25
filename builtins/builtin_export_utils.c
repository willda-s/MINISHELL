/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 20:03:53 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/25 20:04:56 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"

void	set_new_value(t_env *tmp, t_env *new_var)
{
	free(tmp->value);
	tmp->value = new_var->value;
	free(new_var->key);
	free(new_var);
}