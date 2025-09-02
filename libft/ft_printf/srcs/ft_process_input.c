/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:21:54 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/02 16:49:08 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

ssize_t	ft_process_input(const char *input, va_list args, t_vector *buffer)
{
	ssize_t	printed;
	ssize_t	print;

	printed = 0;
	while (*input)
	{
		if (*input == '%')
		{
			input++;
			print = ft_process_format(input, args, buffer);
			if (print == -1)
				return (-1);
			printed += print;
			if (*input)
				input++;
		}
		else
		{
			if (print_char(*input, buffer) == -1)
				return (-1);
			printed++;
			input++;
		}
	}
	return (printed);
}
