/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:41 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/25 20:37:36 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "parsing.h"
#include <stdlib.h>
#include <readline/readline.h>

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
	if (data->env)
	{
		free_lst_env(&data->env, false, 0);
		data->env = NULL;
	}
	free_tmpall(data);
	rl_clear_history();
	ft_dprintf(2, "%s\n", str);
	exit(errcode);
}

void	free_all(t_data *data, bool quit, int errcode)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->env)
	{
		free_lst_env(&data->env, false, 0);
		data->env = NULL;
	}
	free_tmpall(data);
	if (data->fd_backup_in != -1)
		close(data->fd_backup_in);
	if (data->fd_backup_out != -1)
		close(data->fd_backup_out);
	rl_clear_history();
	if (quit)
		exit(errcode);
}

void	free_tmpall(t_data *data)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
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
	{
		free_tab(data->dst);
		data->dst = NULL;
	}
}
