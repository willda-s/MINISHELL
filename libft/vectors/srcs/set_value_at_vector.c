/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value_at_vector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:54:54 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 19:03:10 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vectors.h"

/**
 * set_value_at_vector - Sets a value at a specific index in the vector
 * @vec: Pointer to the vector structure
 * @data: Pointer to the data to be set
 * @i: Index where the value should be set
 * 
 * This function sets a value at the specified index, automatically expanding
 * the vector's capacity if necessary. It implements dynamic allocation
 * management by:
 * 
 * 1. Checking if the target index exceeds current allocation
 * 2. Expanding capacity using exponential growth if needed
 * 3. Resizing the vector to accommodate the new capacity
 * 4. Copying the data to the target position
 * 5. Updating the vector size if the index extends beyond current size
 * 
 * The function allows sparse arrays by setting values at any index,
 * potentially leaving gaps that are zero-initialized.
 * 
 * Return: 0 on success, -1 if memory allocation fails during resize
 */
int	set_value_at_vector(t_vector *vec, const void *data, size_t i)
{
	size_t	j;
	size_t	currentelem;

	if (i >= vec->allocated)
	{
		while (i >= vec->allocated)
		{
			if (vec->allocated == 0)
				vec->allocated = BASE_ALLOC;
			else
				vec->allocated *= 2;
		}
		if (resize_vector(vec) == -1)
			return (-1);
	}
	j = 0;
	currentelem = i * vec->elemsize;
	if (j < vec->elemsize)
		ft_memcpy((char *)vec->array + currentelem, data, vec->elemsize);
	if (i > vec->size)
		vec->size = i;
	return (0);
}
