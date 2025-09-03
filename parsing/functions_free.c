/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:41 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/03 17:36:51 by akarapkh         ###   ########.fr       */
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

int	free_all_msg(t_data *data, int errcode, char *str)
{
	free_tmpall(data);
	ft_dprintf(2, "%s\n", str);
	exit(errcode);
}

int	free_all(t_data *data, int errcode)
{
	if (data->input)
		free(data->input);
	if (data->env)
	{
		free_lst_env(&data->env, false, 0);
		data->env = NULL;
	}
	if (data->pars)
	{
		free_lst_pars(&data->pars);
		data->pars = NULL;
	}
	if (data->exec)
	{
		free_lst_exec(&data->exec);
		data->exec = NULL;
	}
	if (data->envp)
	{
		free_tab(data->envp);
		data->envp = NULL;
	}
	if (data->dst)
		free_tab(data->dst);
	exit(errcode);
}

void	free_tmpall(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->pars)
	{
		free_lst_pars(&data->pars);
		data->pars = NULL;
	}
	if (data->exec)
	{
		free_lst_exec(&data->exec);
		data->exec = NULL;
	}
	if (data->envp)
	{
		free_tab(data->envp);
		data->envp = NULL;
	}
	if (data->dst)
	{
		free_tab(data->dst);
		data->dst = NULL;
	}
}
