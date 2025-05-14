/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:32:11 by willda-s          #+#    #+#             */
/*   Updated: 2024/11/27 15:06:19 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				i;
	char			*b;
	unsigned char	tmp;

	i = 0;
	b = NULL;
	tmp = (unsigned char)c;
	while (str[i])
	{
		if (tmp == (unsigned char)str[i])
			b = (char *)&str[i];
		i++;
	}
	if (tmp == '\0')
		b = (char *)&str[i];
	return (b);
}
