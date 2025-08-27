/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_alloc_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:43:31 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 19:01:58 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

/**
 * set_alloc_size - Adjusts the allocation size for a vector
 * @vec: Pointer to the vector structure
 * @count: Number of elements to be added
 * 
 * This function manages the growth strategy for dynamic vectors by adjusting
 * the allocated capacity when needed. It implements an exponential growth
 * pattern to minimize the number of reallocations:
 * 
 * - For uninitialized vectors (allocated == 0): Sets initial capacity to 
 BASE_ALLOC
 * - For vectors needing more space: Doubles the current capacity
 * 
 * The function only modifies the allocation size if the current capacity
 * is insufficient to hold the existing elements plus the new count, leaving
 * room for a sentinel value (allocated - 1).
 */
void	set_alloc_size(t_vector *vec, size_t count)
{
	if (vec->allocated == 0 || vec->size + count >= vec->allocated - 1)
	{
		if (vec->allocated == 0)
			vec->allocated = BASE_ALLOC;
		else
			vec->allocated *= 2;
		return ;
	}
}
