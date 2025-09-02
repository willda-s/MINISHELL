/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_dif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:31:42 by akarapkh          #+#    #+#             */
/*   Updated: 2025/07/31 17:38:33 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len_dif(const char *str1, const char *str2)
{
	ssize_t	dif;
	ssize_t	len1;
	ssize_t	len2;

	dif = 0;
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	dif = len2 - len1;
	if (dif < 0)
		dif *= -1;
	return (dif);
}
