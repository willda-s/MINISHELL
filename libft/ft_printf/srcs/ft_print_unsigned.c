/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:48:40 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/11 20:23:48 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	print_unsigned(unsigned int n, t_vector *buffer)
{
	int		count;
	int		res;
	char	c;

	count = 0;
	if (n > 9)
	{
		res = print_unsigned(n / 10, buffer);
		if (res == -1)
			return (-1);
		count += res;
	}
	c = (n % 10) + '0';
	if (add_vector(buffer, &c, sizeof(char)) == -1)
		return (-1);
	return (count + 1);
}
