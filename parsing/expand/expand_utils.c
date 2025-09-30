/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:29 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/26 03:39:26 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

char	*get_env_value(t_env *envd, char *key)
{
	while (envd)
	{
		if (ft_strcmp(envd->key, key) == 0)
			return (envd->value);
		envd = envd->next;
	}
	return ((void *)1);
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
