/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 04:59:39 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/25 18:21:44 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

void	update_value(t_env *tmp, t_env *new_var)
{
	free(tmp->value);
	tmp->value = new_var->value;
	free(new_var->key);
	free(new_var);
}
