/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:43:05 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/11 20:23:48 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	print_hex(uintptr_t num, char format, t_vector *buffer)
{
	int		len;
	char	*base;
	int		res;

	len = 0;
	if (format == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (num >= 16)
	{
		res = print_hex(num / 16, format, buffer);
		if (res == -1)
			return (-1);
		len += res;
	}
	res = print_char(base[num % 16], buffer);
	if (res == -1)
		return (-1);
	len += res;
	return (len);
}

int	print_pointer(void *ptr, t_vector *buffer)
{
	int			len;
	int			res;
	uintptr_t	address;

	if (!ptr)
		return (print_string("(nil)", buffer));
	len = print_string("0x", buffer);
	if (len == -1)
		return (-1);
	address = (uintptr_t)ptr;
	res = print_hex(address, 'x', buffer);
	if (res == -1)
		return (-1);
	len += res;
	return (len);
}
