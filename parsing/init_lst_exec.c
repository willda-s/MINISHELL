/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:54 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/29 21:55:52 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static char		**init_cmds(t_data *data, t_pars *tmp, t_exec **node);
static size_t	count_cmd(t_pars *pars);
static int		fill_args(t_pars *pars, t_exec *node);

void	init_lst_exec(t_data *data)
{
	t_exec	*node;
	t_pars	*tmp;

	node = NULL;
	tmp = data->pars;
	while (tmp)
	{
		if (add_back_exec(&(data)->exec) == 1)
			free_all_msg(data, 0, "Error\nAdd_back fail in init_lst_exec\n");
		node = ft_lstlast_exec(data->exec);
		if (!node)
			free_all_msg(data, 0, "Error\nFt_lstlast fail\n");
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

static char	**init_cmds(t_data *data, t_pars *tmp, t_exec **node)
{
	size_t	ccmd;

	if (tmp->type == COMMANDS || tmp->type == BUILTINS)
	{
		ccmd = count_cmd(tmp);
		(*node)->cmd = malloc(sizeof(char *) * (ccmd + 1));
		if (!(*node)->cmd)
			free_all_msg(data, 0, "Error\nMalloc fail in init_cmds\n");
		(*node)->cmd[0] = ft_strdup(tmp->word);
		if (!(*node)->cmd[0])
			free_all_msg(data, 0, "Error\nMalloc fail in init_cmds\n");
		if (fill_args(tmp->next, *node) == 1)
			free_all_msg(data, 0, "Error\nMalloc fail in fill_args\n");
	}
	else
		(*node)->cmd = NULL;
	return ((*node)->cmd);
}

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
