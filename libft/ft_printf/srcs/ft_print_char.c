/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:41:43 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/02 16:47:00 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

int	print_char(char c, t_vector *buffer)
{
	if (add_vector(buffer, &c, sizeof(char)) == -1)
		return (-1);
	return (1);
}
