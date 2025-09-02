/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserve_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:15:02 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/01 19:56:31 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include <stddef.h>

int	reserve_vector(t_vector *vector, size_t size)
{
	size_t	count;

	count = 0;
	if (!vector)
		return (-1);
	if (vector->allocated >= size)
		return (0);
	count = size - vector->allocated;
	set_alloc_size(vector, count);
	if (resize_vector(vector) == -1)
		return (-1);
	return (0);
}
