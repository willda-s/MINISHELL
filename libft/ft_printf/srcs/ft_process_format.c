/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:12:44 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/29 13:33:26 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fd_printf.h"

ssize_t	ft_process_format(const char *input, va_list args, t_vector *buffer)
{
	if (*input == '%')
		return (print_char('%', buffer));
	else if (ft_strchr("cspdiuxX", *input))
		return (ft_input_check(input, args, buffer));
	else
		return (print_char(*input, buffer));
}
