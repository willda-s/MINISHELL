/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:55:47 by williamguer       #+#    #+#             */
/*   Updated: 2024/11/22 19:04:01 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlenint(int n)
{
	size_t	i;

	i = 0;
	if (n == INT_MIN)
		return (11);
	if (n <= 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	i;
	size_t	len;
	char	*result;
	long	nbr;

	len = ft_strlenint(n);
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
