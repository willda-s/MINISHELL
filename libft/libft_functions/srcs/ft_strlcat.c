/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:libft/libft_functions/srcs/ft_strchr_index.c
/*   Created: 2025/07/01 20:42:50 by akarapkh          #+#    #+#             */
/*   Updated: 2025/07/01 21:02:03 by akarapkh         ###   ########.fr       */
========
/*   Created: 2024/11/13 06:50:15 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 14:19:55 by akarapkh         ###   ########.fr       */
>>>>>>>> parsing:libft/libft_functions/srcs/ft_strlcat.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_strchr_index(const char *s, char c)
{
<<<<<<<< HEAD:libft/libft_functions/srcs/ft_strchr_index.c
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
========
	size_t	i;
	size_t	len_dest;
	size_t	len_src;

	i = 0;
	len_dest = 0;
	while (dst[len_dest] && len_dest < size)
		len_dest++;
	len_src = 0;
	while (src[len_src])
		len_src++;
	while (src[i] && len_dest + i + 1 < size)
	{
		dst[len_dest + i] = src[i];
		i++;
	}
	if (len_dest + i < size)
		dst[len_dest + i] = '\0';
	return (len_dest + len_src);
>>>>>>>> parsing:libft/libft_functions/srcs/ft_strlcat.c
}
