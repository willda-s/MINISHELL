/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:12:01 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/09 17:36:14 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vectors.h"

int	merge_vector(t_vector *from, t_vector *to, size_t i)
{
	if (!from || !to || !from->array || !to->array)
		return (-1);
	if (i > to->size)
		return (-1);
	if (from->elemsize != to->elemsize)
		return (-1);
	while (to->size + from->size >= to->allocated)
	{
		set_alloc_size(to, from->size);
		if (resize_vector(to))
			return (-1);
	}
	ft_memmove(to->array + ((i + from->size) * to->elemsize), to->array + i
		* to->elemsize, (to->size - i) * to->elemsize);
	ft_memcpy(to->array + i * to->elemsize, from->array, from->size
		* from->elemsize);
	to->size += from->size;
	return (0);
}
