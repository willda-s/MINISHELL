/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:24:09 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/29 13:33:07 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

int	print_hex_upper(unsigned int num, t_vector *buffer)
{
	int		len;
	char	*base;
	int		res;

	len = 0;
	base = "0123456789ABCDEF";
	if (num >= 16)
	{
		res = print_hex_upper((num / 16), buffer);
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

int	print_hex_lower(unsigned int num, t_vector *buffer)
{
	int		len;
	char	*base;
	int		res;

	len = 0;
	base = "0123456789abcdef";
	if (num >= 16)
	{
		res = print_hex_lower((num / 16), buffer);
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
