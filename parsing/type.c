/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:55:59 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/02 16:33:34 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

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

static void	init_token_brace(t_pars **pars)
{
	t_pars	*tmp;

	tmp = *pars;
	while (tmp)
	{
		if (ft_strcmp(tmp->word, "(") == 0)
			tmp->type = OPEN_BRACE;
		else if (ft_strcmp(tmp->word, ")") == 0)
			tmp->type = CLOSED_BRACE;
		tmp = tmp->next;
	}
}

void	token_main(t_data *data)
{
	init_token_redir(&data->pars);
	init_token_pipe(&data->pars);
	init_token_brace(&data->pars);
	init_token_command(&data->pars);
}
