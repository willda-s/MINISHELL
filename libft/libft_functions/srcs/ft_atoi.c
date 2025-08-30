/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:52:13 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 14:19:55 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_atol(const char *nptr);
static long int	next(long int nb, char next);

int	ft_atoi(const char *nptr)
{
	return (ft_atol(nptr));
}

static long int	ft_atol(const char *nptr)
{
	size_t		i;
	long int	res;

	res = 0;
	i = 0;
	while (nptr[0] == ' ' || (nptr[0] >= '\t' && nptr[0] <= '\r'))
		nptr++;
	if (nptr[i] == '+' || nptr[i] == '-')
		++i;
	while (ft_isdigit(nptr[i]))
	{
		res = next(res, nptr[i]);
		if (res == -1 && nptr[0] == '-')
			return (LONG_MIN);
		else if (res == -1)
			return (LONG_MAX);
		++i;
	}
	if (nptr[0] == '-')
		return (res * -1);
	return (res);
}

static long int	next(long int res, char next)
{
	if (res > LONG_MAX / 10)
		return (-1);
	res *= 10;
	if (res > LONG_MAX - (next - '0'))
		return (-1);
	res += (next - '0');
	return (res);
}
