/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:55:44 by williamguer       #+#    #+#             */
/*   Updated: 2025/04/25 19:11:32 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	address_nbr(unsigned long n)
{
	size_t	nbr;

	nbr = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		nbr += 1;
		n /= 16;
	}
	return (nbr);
}

void	ft_putaddress(unsigned long n, bool upper_case)
{
	char	*strupper;
	char	*strlower;

	strupper = "0123456789ABCDEF";
	strlower = "0123456789abcdef";
	if (n >= 16)
		ft_putaddress((n / 16), upper_case);
	if (upper_case == true)
		write(1, &strupper[n % 16], 1);
	else
		write(1, &strlower[n % 16], 1);
}

int	prt_address(unsigned long n, bool upper_case)
{
	if (!n)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	ft_putaddress(n, upper_case);
	return (address_nbr(n) + 2);
}
