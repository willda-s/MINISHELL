/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 07:32:24 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/30 20:34:02 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	total_size;

	total_size = nmemb * size;
	if (total_size == 0)
	{
		res = malloc(0);
		return (res);
	}
	if (total_size / size != nmemb)
		return (NULL);
	res = malloc(total_size);
	if (!res)
		return (NULL);
	ft_memset(res, 0, total_size);
	return (res);
}
