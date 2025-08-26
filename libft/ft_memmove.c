/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:33:57 by willda-s          #+#    #+#             */
/*   Updated: 2024/11/22 14:43:51 by willda-s         ###   ########.fr       */
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

// int	main(void)
// {
// 	unsigned long src = 0xdeadbeef;
// 	int size = sizeof(src);

// 	unsigned long dst1;
// 	unsigned long dst2;
// 	printf("%s\n", (char *)ft_memmove(&dst2, &src, size));
// 	return (0);
// }