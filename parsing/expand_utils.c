/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:29 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/18 22:42:46 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

char	*get_env_value(t_env *envd, char *key)
{
	while (envd)
	{
		if (ft_strcmp(envd->key, key) == 0)
			return (envd->value);
		envd = envd->next;
	}
	return ("");
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
