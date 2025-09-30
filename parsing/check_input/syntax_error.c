/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:23:20 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/29 22:59:19 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft_dprintf.h"

int	syntax_error(int type)
{
	static const char *const	op_type[] = {
	[PIPE] = "|",
	[DOUBLE_PIPE] = "||",
	[REDIR_IN] = "<",
	[REDIR_TRUNC] = ">",
	[HEREDOC] = "<<",
	[REDIR_APPEND] = ">>",
	[OPEN_BRACE] = "(",
	[CLOSED_BRACE] = ")",
	[SIMPLE_QUOTE] = "\'",
	[DOUBLE_QUOTE] = "\"",
	[BACK_SLASH] = "\\",
	};

	ft_dprintf(STDERR_FILENO, SYNTAX_ERR, op_type[type]);
	return (1);
}
