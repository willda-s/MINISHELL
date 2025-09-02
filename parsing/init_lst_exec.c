/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:54 by willda-s          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2025/08/30 16:15:11 by akarapkh         ###   ########.fr       */
=======
/*   Updated: 2025/08/28 13:29:26 by willda-s         ###   ########.fr       */
>>>>>>> cam
=======
/*   Updated: 2025/08/31 22:14:21 by willda-s         ###   ########.fr       */
>>>>>>> parsing
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	count_cmd(t_pars *pars)
{
	size_t	i;

	i = 0;
	if (pars->type == COMMANDS || pars->type == BUILTINS)
	{
		i++;
		pars = pars->next;
		while (pars && pars->type != PIPE)
		{
			if (pars->type == ARGS)
				i++;
			pars = pars->next;
		}
	}
	return (i);
}

static int	fill_args(t_pars *pars, t_exec *node)
{
	int	i;

	i = 1;
	while (pars && pars->type != PIPE)
	{
		if (pars->type == ARGS)
		{
			node->cmd[i] = ft_strdup(pars->word);
			if (!node->cmd[i])
				return (1);
			i++;
		}
		pars = pars->next;
	}
	node->cmd[i] = NULL;
	return (0);
}

static char	**init_cmds(t_data *data, t_pars *tmp, t_exec **node)
{
	size_t	ccmd;

	if (tmp->type == COMMANDS || tmp->type == BUILTINS)
	{
		ccmd = count_cmd(tmp);
		(*node)->cmd = malloc(sizeof(char *) * (ccmd + 1));
		if (!(*node)->cmd)
<<<<<<< HEAD
<<<<<<< HEAD
			free_all_msg(data, 0, "Error\nMalloc fail in init_cmds\n");
		(*node)->cmd[0] = ft_strdup(tmp->word);
		if (!(*node)->cmd[0])
			free_all_msg(data, 0, "Error\nMalloc fail in init_cmds\n");
		if (fill_args(tmp->next, *node) == 1)
			free_all_msg(data, 0, "Error\nMalloc fail in fill_args\n");
=======
			free_all(data, 0, "Error\nMalloc fail in init_cmds\n", true);
=======
			free_all(data, 12, "Error\nMalloc fail in init_cmds\n", true);
>>>>>>> parsing
		(*node)->cmd[0] = ft_strdup(tmp->word);
		if (!(*node)->cmd[0])
			free_all(data, 12, "Error\nMalloc fail in init_cmds\n", true);
		if (fill_args(tmp->next, *node) == 1)
<<<<<<< HEAD
			free_all(data, 0, "Error\nMalloc fail in fill_args\n", true);
>>>>>>> cam
=======
			free_all(data, 12, "Error\nMalloc fail in fill_args\n", true);
>>>>>>> parsing
	}
	else
		(*node)->cmd = NULL;
	return ((*node)->cmd);
}

void	init_lst_exec(t_data *data)
{
	t_exec	*node;
	t_pars	*tmp;

	node = NULL;
	tmp = data->pars;
	while (tmp)
	{
		if (add_back_exec(&(data)->exec) == 1)
<<<<<<< HEAD
			free_all_msg(data, 0, "Error\nAdd_back fail in init_lst_exec\n");
		node = ft_lstlast_exec(data->exec);
		if (!node)
			free_all_msg(data, 0, "Error\nFt_lstlast fail\n");
=======
			free_all(data, 0, "Error\nAdd_back fail in init_lst_exec\n", true);
		node = ft_lstlast_exec(data->exec);
		if (!node)
			free_all(data, 0, "Error\nFt_lstlast fail\n", true);
>>>>>>> cam
		while (tmp && tmp->type != PIPE)
		{
			if (!node->cmd)
				node->cmd = init_cmds(data, tmp, &node);
			node->fd_in = -1;
			node->fd_out = -1;
			init_lst_redir(&node, tmp, data);
			tmp = tmp->next;
		}
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
	}
}
