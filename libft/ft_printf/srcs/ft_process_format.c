/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:12:44 by akarapkh          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/29 13:33:26 by akarapkh         ###   ########.fr       */
=======
/*   Updated: 2025/06/28 14:19:22 by akarapkh         ###   ########.fr       */
>>>>>>> parsing
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
<<<<<<< HEAD
#include "fd_printf.h"
=======
#include "../includes/fd_printf.h"
>>>>>>> parsing

ssize_t	ft_process_format(const char *input, va_list args, t_vector *buffer)
{
	if (*input == '%')
		return (print_char('%', buffer));
	else if (ft_strchr("cspdiuxX", *input))
		return (ft_input_check(input, args, buffer));
	else
		return (print_char(*input, buffer));
}
