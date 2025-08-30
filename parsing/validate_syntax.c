/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:26:59 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/30 18:05:05 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static int	check_syntax(t_pars *pars);
static int	check_curr_and_next_token(t_pars *curr, t_pars *next);
static int	is_syntax_error(t_pars *curr, t_pars *next);
static int	contains_double_pipe(char *word);

int	validate_syntax(t_pars *pars)
{
	if (!pars)
		return (0);
	if (pars->type == PIPE)
		return (syntax_error(PIPE));
	if (pars->type == OPEN_BRACE || pars->type == CLOSED_BRACE)
		return (syntax_error(pars->type));
	return (check_syntax(pars));
}

static int	check_syntax(t_pars *pars)
{
	int	result;

	if (pars->next)
	{
		result = check_curr_and_next_token(pars, pars->next);
		if (result != 0)
			return (result);
		return (check_syntax(pars->next));
	}
	else
		return (check_curr_and_next_token(pars, NULL));
}

static int	check_curr_and_next_token(t_pars *curr, t_pars *next)
{
	if (contains_double_pipe(curr->word))
		return (syntax_error(PIPE));
	if (curr->type == OPEN_BRACE || curr->type == CLOSED_BRACE)
		return (syntax_error(curr->type));
	if (next)
	{
		if (contains_double_pipe(next->word))
			return (syntax_error(PIPE));
		if (next->type == OPEN_BRACE || next->type == CLOSED_BRACE)
			return (syntax_error(next->type));
		if (is_syntax_error(curr, next))
			return (syntax_error(next->type));
	}
	else
	{
		if (curr->type == PIPE || (curr->type & REDIR))
			return (syntax_error(curr->type));
	}
	return (0);
}

static int	is_syntax_error(t_pars *tok1, t_pars *tok2)
{
	if ((tok1->type & REDIR) && tok2->type != TARGETS)
		return (1);
	if (tok1->type == PIPE && tok2->type == PIPE)
		return (1);
	if (tok1->type == PIPE && (tok2->type & REDIR))
		return (1);
	return (0);
}

static int	contains_double_pipe(char *word)
{
	if (!word)
		return (0);
	if (ft_strncmp(word, "||", 2) == 0)
		return (1);
	return (0);
}
