/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:55:44 by williamguer       #+#    #+#             */
/*   Updated: 2025/04/25 19:11:32 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	hexa_nbr(unsigned int n)
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

void	ft_puthexa(unsigned int n, bool upper_case)
{
	char	*strupper;
	char	*strlower;

	strupper = "0123456789ABCDEF";
	strlower = "0123456789abcdef";
	if (n >= 16)
		ft_puthexa((n / 16), upper_case);
	if (upper_case == true)
		write(1, &strupper[n % 16], 1);
	else
		write(1, &strlower[n % 16], 1);
}

int	prt_hexa(unsigned int n, bool upper_case)
{
	ft_puthexa(n, upper_case);
	return (hexa_nbr(n));
}
