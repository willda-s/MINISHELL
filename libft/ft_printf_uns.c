/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:55:47 by williamguer       #+#    #+#             */
/*   Updated: 2025/04/25 19:11:32 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlenint_unsigned(unsigned int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	size_t	i;
	size_t	len;
	char	*result;
	long	nbr;

	len = ft_strlenint_unsigned(n);
	i = len - 1;
	nbr = n;
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	result[0] = '0';
	if (nbr < 0)
	{
		nbr = -nbr;
		result[0] = '-';
	}
	while (nbr != 0)
	{
		result[i] = ((nbr % 10) + 48);
		nbr /= 10;
		i--;
	}
	result[len] = '\0';
	return (result);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int		len;
	char	*res;

	len = 0;
	res = ft_itoa_unsigned(n);
	len = ft_putstr(res);
	free(res);
	return (len);
}
