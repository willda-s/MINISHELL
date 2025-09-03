/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:00:48 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/03 14:01:15 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

void	is_builtins(t_pars **tmp)
{
	if (ft_strncmp((*tmp)->word, "cd", ft_strlen((*tmp)->word)) == 0
		|| ft_strncmp((*tmp)->word, "echo", ft_strlen((*tmp)->word)) == 0
		|| ft_strncmp((*tmp)->word, "pwd", ft_strlen((*tmp)->word)) == 0
		|| ft_strncmp((*tmp)->word, "export", ft_strlen((*tmp)->word)) == 0
		|| ft_strncmp((*tmp)->word, "unset", ft_strlen((*tmp)->word)) == 0
		|| ft_strncmp((*tmp)->word, "env", ft_strlen((*tmp)->word)) == 0
		|| ft_strncmp((*tmp)->word, "exit", ft_strlen((*tmp)->word)) == 0)
	{
		(*tmp)->type = BUILTINS;
	}
}

bool	is_redirection(t_pars **tmp)
{
	if (ft_strncmp((*tmp)->word, ">", ft_strlen((*tmp)->word)) == 0)
		(*tmp)->type = REDIR_TRUNC;
	else if (ft_strncmp((*tmp)->word, "<", ft_strlen((*tmp)->word)) == 0)
		(*tmp)->type = REDIR_IN;
	else if (ft_strncmp((*tmp)->word, "<<", ft_strlen((*tmp)->word)) == 0)
		(*tmp)->type = HEREDOC;
	else if (ft_strncmp((*tmp)->word, ">>", ft_strlen((*tmp)->word)) == 0)
		(*tmp)->type = REDIR_APPEND;
	if ((*tmp)->type != NUL)
		return (true);
	else
		return (false);
}
