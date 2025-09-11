/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:23:25 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/11 20:23:48 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

ssize_t	ft_input_check(const char *input, va_list args, t_vector *buffer)
{
	ssize_t	i;
	ssize_t	error_output;

	i = 0;
	error_output = 0;
	if (*input == 'c')
		error_output = print_char(va_arg(args, int), buffer);
	else if (*input == 's')
		error_output = print_string(va_arg(args, char *), buffer);
	else if (*input == 'p')
		error_output = print_pointer(va_arg(args, void *), buffer);
	else if (*input == 'd' || *input == 'i')
		error_output = print_int(va_arg(args, int), buffer);
	else if (*input == 'u')
		error_output = print_unsigned(va_arg(args, unsigned int), buffer);
	else if (*input == 'x')
		error_output = print_hex_lower(va_arg(args, unsigned int), buffer);
	else if (*input == 'X')
		error_output = print_hex_upper(va_arg(args, unsigned int), buffer);
	if (error_output == -1)
		return (-1);
	i += error_output;
	return (i);
}
