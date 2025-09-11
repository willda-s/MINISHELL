/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:29 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/11 20:16:59 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

char	*get_env_value(t_env *envd, char *key)
{
	while (envd)
	{
		if (ft_strncmp(envd->key, key, ft_strlen(envd->key)) == 0)
		{
			return (envd->value);
		}
		envd = envd->next;
	}
	return ("");
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
