/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_and_pars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:46 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/27 05:43:44 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static int	init_lst_pars(t_pars **pars, char **dst);

void	init_data(t_data *data, t_env **envd, char **dst)
{
	t_pars	*pars;
	t_exec	*exec;

	pars = NULL;
	exec = NULL;
	data->dst = dst;
	if (!data->env)
		data->env = *envd;
	data->envp = NULL;
	// if (!data->input)
	// 	data->input = NULL;
	data->i = 0;
	// data->errcode = 0;
	data->fd_backup_in = -1;
	data->fd_backup_out = -1;
	if (init_lst_pars(&pars, data->dst) == 1)
	{
		free_lst_pars(&pars);
		free_tab(dst);
		// free_lst_env(envd, true, 0);
		data->errcode = 1;
		return ;
	}
	data->pars = pars;
	data->exec = exec;
}

static int	init_lst_pars(t_pars **pars, char **dst)
{
	t_pars	*node;
	int		i;

	i = 0;
	while (dst && dst[i])
	{
		if (add_back_pars(pars) == 1)
			return (1);
		node = ft_lstlast_pars(*pars);
		if (!node)
			return (1);
		node->word = ft_strdup(dst[i]);
		if (!node->word)
			return (1);
		node->type = NUL;
		i++;
	}
	return (0);
}
