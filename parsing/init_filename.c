/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_filename.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:50 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/02 17:31:13 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static void	check_redirin(t_data *data, t_pars *tmp, t_redir **node)
{
	if (tmp->type == REDIR_IN && tmp->next)
	{
		(*node)->filename = ft_strdup(tmp->next->word);
		if (!(*node)->filename)
			free_all_msg(data, 0, "Error\nMalloc fail in check_redirin\n");
		(*node)->token = REDIR_IN;
	}
	else if (tmp->type == HEREDOC && tmp->next && (*node)->token != HEREDOC)
	{
		(*node)->delimiter = ft_strdup(tmp->next->word);
		if (!(*node)->delimiter)
			free_all_msg(data, 0, "Error\nMalloc fail in check_redirin\n");
		(*node)->token = HEREDOC;
	}
}

static void	check_redirout(t_data *data, t_pars *tmp, t_redir **node)
{
	if (tmp->type == REDIR_APPEND && tmp->next)
	{
		(*node)->filename = ft_strdup(tmp->next->word);
		if (!(*node)->filename)
			free_all_msg(data, 0, "Error\nMalloc fail in check_redirout\n");
		(*node)->token = REDIR_APPEND;
	}
	else if (tmp->type == REDIR_TRUNC && tmp->next)
	{
		(*node)->filename = ft_strdup(tmp->next->word);
		if (!(*node)->filename)
			free_all_msg(data, 0, "Error\nMalloc fail in check_redirout\n");
		(*node)->token = REDIR_TRUNC;
	}
}

static void	init_filename_and_token(t_redir **node, t_pars *tmp, t_data *data)
{
	if (tmp && tmp->type & REDIR)
	{
		check_redirin(data, tmp, node);
		check_redirout(data, tmp, node);
	}
}

void	init_lst_redir(t_exec **exec, t_pars *pars, t_data *data)
{
	t_redir	*node;

	node = NULL;
	if (pars && pars->type & REDIR)
	{
		if (add_back_redir(&(*exec)->redir) == 1)
			free_all_msg(data, 0, "Error\nAdd_back fail in init_lst_redir\n");
		node = ft_lstlast_redir((*exec)->redir);
		if (!node)
			free_all_msg(data, 0, "Error\nFt_lstlast_redir fail\n");
		init_filename_and_token(&node, pars, data);
	}
}
