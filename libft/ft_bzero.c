/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:23:09 by willda-s          #+#    #+#             */
/*   Updated: 2024/11/18 16:43:42 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)s;
	while (i < n)
	{
		tmp[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	int		i;
	int		len;
	char	*str;

	str[] = "salutf";
	i = 0;
	len = strlen(str);
	ft_bzero(str, 5);
	while (i < len)
	{
		putchar(str[i]);
		i++;
	}
}*/
