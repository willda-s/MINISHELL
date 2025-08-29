/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   */
/*   Created: 2024/11/17 16:32:00 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/23 17:00:00 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

static int	print_positive_int(unsigned int n, t_vector *buffer)
{
	int		count;
	int		res;
	char	c;

	count = 0;
	if (n > 9)
	{
		res = print_positive_int(n / 10, buffer);
		if (res == -1)
			return (-1);
		count += res;
	}
	c = (n % 10) + '0';
	if (add_vector(buffer, &c, sizeof(char)) == -1)
		return (-1);
	return (count + 1);
}

int	print_int(int n, t_vector *buffer)
{
	int		count;
	int		res;
	char	c;

	count = 0;
	if (n == -2147483648)
		return (print_string("-2147483648", buffer));
	if (n < 0)
	{
		c = '-';
		if (add_vector(buffer, &c, sizeof(char)) == -1)
			return (-1);
		count++;
		n = -n;
	}
	res = print_positive_int((unsigned int)n, buffer);
	if (res == -1)
		return (-1);
	return (count + res);
}
