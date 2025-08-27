/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:41 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/27 20:23:06 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"
#include "parsing.h"

void	free_tab(char **dst)
{
	int	i;

	i = 0;
	while (dst && dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
}

int	free_all(t_data *data, int errcode, char *str)
{
	if (data->env)
		free_lst_env(&data->env, false, 0);
	if (data->pars)
		free_lst_pars(&data->pars);
	if (data->exec)
		free_lst_exec(&data->exec);
	if (data->envp)
		free_tab(data->envp);
	if (data->dst)
		free_tab(data->dst);
	ft_dprintf(2, "%s\n", str);
	exit(errcode);
}
