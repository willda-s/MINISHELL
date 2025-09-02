/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
<<<<<<< HEAD:libft/libft_functions/srcs/ft_strncmp.c
/*   Created: 2024/11/07 16:17:05 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 14:19:55 by akarapkh         ###   ########.fr       */
=======
/*   Created: 2024/11/05 16:03:38 by willda-s          #+#    #+#             */
/*   Updated: 2025/06/30 14:22:22 by willda-s         ###   ########.fr       */
>>>>>>> cam:libft/ft_strncmp.c
=======
/*   Created: 2024/11/07 16:17:05 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 14:19:55 by akarapkh         ###   ########.fr       */
>>>>>>> parsing
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
