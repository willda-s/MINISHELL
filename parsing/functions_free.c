/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:41 by willda-s          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2025/09/01 19:53:41 by akarapkh         ###   ########.fr       */
=======
/*   Updated: 2025/08/28 16:38:04 by willda-s         ###   ########.fr       */
>>>>>>> cam
=======
/*   Updated: 2025/08/31 22:33:00 by willda-s         ###   ########.fr       */
>>>>>>> parsing
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

<<<<<<< HEAD
int	free_all_msg(t_data *data, int errcode, char *str)
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

int	free_all(t_data *data, int errcode)
=======
void	free_tmpall(t_data *data)
{
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

void	free_all(t_data *data, int errcode, char *str, bool exitstatue)
>>>>>>> cam
{
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
	{
		free_tab(data->dst);
<<<<<<< HEAD
	exit(errcode);
=======
		data->dst = NULL;
	}
	ft_putstr_fd(str, 2);
	if (exitstatue)
		exit(errcode);
>>>>>>> cam
}

