/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:34:57 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 19:03:28 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vectors.h"

/**
 * add_vector - Adds elements to a dynamic vector
 * @vec: Pointer to the vector structure
 * @data: Pointer to the data to be added
 * @count: Number of elements to add
 * 
 * This function adds one or more elements to a dynamic vector. It automatically
 * resizes the vector if there isn't enough space to accommodate the new 
 elements.
 * The function ensures the vector has sufficient capacity before copying the 
 data.
 * 
 * The resize operation is triggered when the current size plus the count of new
 * elements would exceed the allocated capacity minus one (leaving room for a
 * null terminator or similar sentinel value).
 * 
 * Return: 0 on success, -1 if memory allocation fails during resize
 */
int	add_vector(t_vector *vec, const void *data, size_t count)
{
	size_t	currentelem;

	while (vec->allocated == 0 || vec->size + count >= vec->allocated - 1)
	{
		set_alloc_size(vec, count);
		if (resize_vector(vec))
			return (-1);
	}
	currentelem = vec->size * vec->elemsize;
	ft_memcpy(vec->array + currentelem, data, vec->elemsize * count);
	vec->size += count;
	return (0);
}
