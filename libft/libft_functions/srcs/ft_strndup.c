/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libft/libft_functions/srcs/ft_strndup.c
/*   Created: 2025/08/27 19:59:29 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/27 20:01:48 by akarapkh         ###   ########.fr       */
=======
/*   Created: 2024/11/14 13:17:01 by willda-s          #+#    #+#             */
/*   Updated: 2025/06/30 14:05:21 by willda-s         ###   ########.fr       */
>>>>>>> cam:libft/ft_strjoin.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t len)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
