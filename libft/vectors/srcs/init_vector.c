/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:39:08 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 18:44:23 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

/**
 * init_vector - Initializes a vector structure with default values
 * @vec: Pointer to the vector structure to initialize
 * @elemsize: Size in bytes of each element in the vector
 * 
 * This function sets up a vector for first use by initializing all fields
 * to their default values. The vector starts with no allocated memory and
 * no elements. Memory allocation occurs when the first element is added.
 * 
 * The elemsize parameter is crucial as it determines how much memory to
 * allocate for each element and how to calculate memory offsets when
 * accessing elements.
 */
void	init_vector(t_vector *vec, size_t elemsize)
{
	vec->elemsize = elemsize;
	vec->allocated = 0;
	vec->size = 0;
	vec->array = NULL;
}
