/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:23:20 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/30 16:32:34 by akarapkh         ###   ########.fr       */
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
	[SIMPLE_QUOTE] = "\'",
	[DOUBLE_QUOTE] = "\"",
	};

	ft_dprintf(STDERR_FILENO, SYNTAX_ERR, op_type[type]);
	return (1);
}
