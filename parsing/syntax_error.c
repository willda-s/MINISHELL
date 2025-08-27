/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:26:59 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/27 20:27:25 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	syntax_error(int type)
{
	static const char	*op_type[] = {
	[TOKEN_PIPE] = "|",
	[TOKEN_REDIRECT_IN] = "<",
	[TOKEN_REDIRECT_OUT] = ">",
	[TOKEN_HEREDOC] = "<<",
	[TOKEN_APPEND] = ">>",
	[TOKEN_OPEN_BRACE] = "(",
	[TOKEN_CLOSE_BRACE] = ")",
	[TOKEN_SIMP_QUOTE] = "\'",
	[TOKEN_DOUBLE_QUOTE] = "\""
	};

	ft_dprintf(STDERR_FILENO, SYNTAX_ERR, op_type[type]);
	return (1);
}
