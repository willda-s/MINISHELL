/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:26:59 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/28 21:04:58 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "fd_printf.h"

int	syntax_error(int type)
{
	static const char	*op_type[] = {
	[PIPE] = "|",
	[REDIR_IN] = "<",
	[REDIR_TRUNC] = ">",
	[HEREDOC] = "<<",
	[REDIR_APPEND] = ">>",
	[OPEN_BRACE] = "(",
	[CLOSED_BRACE] = ")",
	};

	ft_dprintf(STDERR_FILENO, SYNTAX_ERR, op_type[type]);
	return (1);
}
#include "parsing.h"
#include <stddef.h>

static int	check_syntax(t_pars *pars);
static int	check_curr_and_next_token(t_pars *curr, t_pars *next);
static int	is_syntax_error(t_pars *curr, t_pars *next);
static int	is_logic_sep(t_pars *token);

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

	if (!pars->next)
		return (0);
	result = check_curr_and_next_token(pars, pars->next);
	if (result != 0)
		return (result);
	return (check_syntax(pars));
}

static int	check_curr_and_next_token(t_pars *curr, t_pars *next)
{
	if (curr->type == OPEN_BRACE || curr->type == CLOSED_BRACE)
		return (syntax_error(curr->type));
	if (next)
	{
		if (next->type == OPEN_BRACE || next->type == CLOSED_BRACE)
			return (syntax_error(next->type));
		if (is_syntax_error(curr, next))
			return (syntax_error(next->type));
	}
	else
	{
		if (curr->type == PIPE || curr->type == REDIR_IN
			|| curr->type == REDIR_TRUNC || curr->type == REDIR_APPEND
			|| curr->type == HEREDOC)
			return (syntax_error(curr->type));
	}
	return (0);
}

static int	is_syntax_error(t_pars *tok1, t_pars *tok2)
{
	if (tok1->type == HEREDOC && tok2->type != TARGETS)
		return (1);
	if (tok1->type == REDIR_APPEND && tok2->type != TARGETS)
		return (1);
	if (tok1->type == REDIR_IN && tok2->type != TARGETS)
		return (1);
	if (tok1->type == REDIR_TRUNC && tok2->type != TARGETS)
		return (1);
	if (is_logic_sep(tok1) && is_logic_sep(tok2))
		return (1);
	if (tok1->type == PIPE && tok2->type == PIPE)
		return (1);
	return (0);
}

static int	is_logic_sep(t_pars *token)
{
	if (token->type & PIPE)
		return (1);
	return (0);
}