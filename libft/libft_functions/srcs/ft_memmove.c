/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 07:33:16 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 14:19:55 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const long int	diff = dest - src;
	size_t			i;

	if (diff > 0)
	{
		while (n > 0)
		{
			--n;
			((char *)(dest))[n] = ((char *)(src))[n];
		}
	}
	else if (diff < 0)
	{
		i = 0;
		while (i < n)
		{
			((char *)(dest))[i] = ((char *)(src))[i];
			++i;
		}
	}
	return (dest);
}
