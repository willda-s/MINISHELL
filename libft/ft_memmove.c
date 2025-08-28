/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:33:57 by willda-s          #+#    #+#             */
/*   Updated: 2025/06/30 14:05:10 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tempdst;
	const char	*tempsrc;

	tempdst = (char *)dst;
	tempsrc = (char *)src;
	if (tempdst > tempsrc)
	{
		while (len-- > 0)
			tempdst[len] = tempsrc[len];
		return (dst);
	}
	return (ft_memcpy(dst, src, len));
}
