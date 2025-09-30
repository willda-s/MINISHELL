/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:00:48 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/23 15:51:24 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

void	is_builtins(t_pars **tmp)
{
	if (ft_strcmp((*tmp)->word, "cd") == 0
		|| ft_strcmp((*tmp)->word, "echo") == 0
		|| ft_strcmp((*tmp)->word, "pwd") == 0
		|| ft_strcmp((*tmp)->word, "export") == 0
		|| ft_strcmp((*tmp)->word, "unset") == 0
		|| ft_strcmp((*tmp)->word, "env") == 0
		|| ft_strcmp((*tmp)->word, "exit") == 0)
	{
		(*tmp)->type = BUILTINS;
	}
}

bool	is_redirection(t_pars **tmp)
{
	if (ft_strcmp((*tmp)->word, ">") == 0)
		(*tmp)->type = REDIR_TRUNC;
	else if (ft_strcmp((*tmp)->word, "<") == 0)
		(*tmp)->type = REDIR_IN;
	else if (ft_strcmp((*tmp)->word, "<<") == 0)
		(*tmp)->type = HEREDOC;
	else if (ft_strcmp((*tmp)->word, ">>") == 0)
		(*tmp)->type = REDIR_APPEND;
	if ((*tmp)->type != NUL)
		return (true);
	else
		return (false);
}

void	init_token_backslash(t_pars **pars)
{
	t_pars	*tmp;

	tmp = *pars;
	while (tmp)
	{
		if (ft_strncmp(tmp->word, "\\", 1) == 0)
			tmp->type = BACK_SLASH;
		tmp = tmp->next;
	}
}
