/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:19:39 by akarapkh          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/29 13:33:22 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"
=======
/*   Updated: 2025/06/23 18:31:22 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fd_printf.h"
>>>>>>> parsing

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
