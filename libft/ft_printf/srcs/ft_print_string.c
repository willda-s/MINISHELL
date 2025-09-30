/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:57:17 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/11 20:23:48 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"

ssize_t	print_string(char *s, t_vector *buffer)
{
	ssize_t	len;
	ssize_t	i;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (add_vector(buffer, &s[i], sizeof(char)) == -1)
			return (-1);
		i++;
	}
	return (len);
}
