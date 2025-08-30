/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:58 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/30 19:31:40 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	lstsize_exec(t_exec *exec)
{
	int	i;

	i = 1;
	if (!exec)
		return (0);
	if (!exec->next)
		return (1);
	while (exec->next)
	{
		exec = exec->next;
		i++;
	}
	return (i);
}

void	free_lst_exec(t_exec **exec)
{
	t_exec	*tmp;
	int		size;

	size = lstsize_exec(*exec);
	if (!(*exec))
		return ;
	while (size--)
	{
		tmp = (*exec)->next;
		if ((*exec)->cmd)
			free_tab((*exec)->cmd);
		if ((*exec)->path)
			free((*exec)->path);
		if ((*exec)->redir)
			free_lst_redir(&(*exec)->redir);
		free(*exec);
		*exec = tmp;
	}
}

t_exec	*ft_lstlast_exec(t_exec *exec)
{
	if (!exec)
		return (exec);
	while (exec->next)
		exec = exec->next;
	return (exec);
}

int	add_back_exec(t_exec **exec)
{
	t_exec	*node;
	t_exec	*tmp;

	node = ft_calloc(1, sizeof(t_exec));
	if (!node)
		return (1);
	node->next = NULL;
	if (!*exec)
		*exec = node;
	else
	{
		tmp = ft_lstlast_exec(*exec);
		tmp->next = node;
	}
	return (0);
}

void	print_lst_exec(t_exec *exec)
{
	int		j;
	int		i;
	t_redir	*tmp;

	j = 0;
	while (exec)
	{
		i = 0;
		printf("-------------noeud [%d]---------------------\n", j++);
		printf("fd_in = %d\n", exec->fd_in);
		printf("fd_out = %d\n", exec->fd_out);
		while (exec->cmd && exec->cmd[i])
		{
			printf("cmd[%d] = %s\n", i, exec->cmd[i]);
			i++;
		}
		tmp = exec->redir;
		while (tmp)
		{
			printf("token = %u\n", tmp->token);
			printf("filename = %s\n", tmp->filename);
			printf("delimiter = %s\n", tmp->delimiter);
			tmp = tmp->next;
		}
		exec = exec->next;
	}
}
