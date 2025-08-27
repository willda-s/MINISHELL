/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:05:42 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/09 19:11:48 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vectors.h"

int	dup_vector(t_vector *src, t_vector *dst)
{
	init_vector(dst, src->elemsize);
	if (reserve_vector(dst, src->size) == -1)
		return (-1);
	ft_memcpy(dst->array, src->array, src->size * src->elemsize);
	dst->size = src->size;
	return (0);
}
