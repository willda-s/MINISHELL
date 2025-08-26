/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:33:15 by willda-s          #+#    #+#             */
/*   Updated: 2024/11/13 18:25:40 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	cc;

	i = 0;
	tmp = (unsigned char *)s;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (tmp[i] == cc)
			return ((void *)&tmp[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char str[] = "saksokd";
	int c = 'g';

	printf("%p\n", ft_memchr(str, c, 5));
	printf("%p", memchr(str, c, 5));
}*/
