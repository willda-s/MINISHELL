/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:55:59 by willda-s          #+#    #+#             */
/*   Updated: 2025/06/30 16:16:16 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static bool	lastnode_pipe(t_pars *pars)
{
	while (pars->next)
		pars = pars->next;
	if (pars->type == PIPE)
		return (true);
	return (false);
}

static void	init_token_command(t_pars **pars)
{
	t_pars	*tmp;

	tmp = *pars;
	while (tmp)
	{
		if (tmp->type == NUL)
		{
			tmp->type = COMMANDS;
			is_builtins(&tmp);
			while (tmp->next && tmp->next->type != PIPE)
			{
				tmp = tmp->next;
				if (tmp->type == NUL)
					tmp->type = ARGS;
			}
		}
		tmp = tmp->next;
	}
}

static void	init_token_redir(t_pars **pars)
{
	t_pars	*tmp;

	tmp = *pars;
	while (tmp)
	{
		if (tmp->type == NUL)
		{
			if (is_redirection(&tmp))
			{
				if (tmp->next)
					tmp->next->type = TARGETS;
			}
		}
		tmp = tmp->next;
	}
}

static void	init_token_pipe(t_pars **pars)
{
	t_pars	*tmp;

	tmp = *pars;
	while (tmp)
	{
		if (ft_strncmp(tmp->word, "|", ft_strlen(tmp->word)) == 0)
			tmp->type = PIPE;
		tmp = tmp->next;
	}
}

void	token_main(t_data *data)
{
	init_token_redir(&data->pars);
	init_token_pipe(&data->pars);
	if (lastnode_pipe(data->pars))
		free_all(data, 0, "Error\nIncorrect syntax\n");
	init_token_command(&data->pars);
}
