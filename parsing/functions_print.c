/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:56:02 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/02 16:36:45 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	print_tab(char **dst)
// {
// 	int	i;

// 	i = 0;
// 	while (dst && dst[i])
// 	{
// 		printf("dst[%d] = %s\n", i, dst[i]);
// 		i++;
// 	}
// }
void	print_lst_env(t_env *envd)
{
	while (envd)
	{
		printf("%s=%s\n", envd->key, envd->value);
		envd = envd->next;
	}
}

// void	print_envp(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// }

