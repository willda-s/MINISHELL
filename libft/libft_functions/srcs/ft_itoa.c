/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:10:13 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 14:19:55 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_nb_len(int n)
{
	int	nb_len;

	nb_len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		nb_len++;
		n /= 10;
	}
	return (nb_len);
}

static long int	ft_nb_is_neg(long int n, int *sign)
{
	*sign = 0;
	if (n < 0)
	{
		*sign = 1;
		return (-n);
	}
	return (n);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		nb_len;
	char	*result;
	long	nb;

	nb = n;
	nb = ft_nb_is_neg(nb, &sign);
	nb_len = ft_nb_len(nb) + sign;
	result = ft_calloc(nb_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (sign)
		result[0] = '-';
	while (nb_len > sign)
	{
		result[--nb_len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (result);
}
