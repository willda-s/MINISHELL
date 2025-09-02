/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:38:14 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/03 13:14:46 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

/**
 * free_vector - Frees the memory allocated for a vector and resets its state
 * @vec: Pointer to the vector structure to free
 *
 * This function safely deallocates the memory used by the vector's data
  array
 * and resets all vector fields to their initial state. It checks if the
 array
 * exists before attempting to free it to prevent double-free errors.
 *
 * After calling this function, the vector is in a clean state and can be
 * reused or safely destroyed. The vector structure itself is not freed,
 * only its internal data array.
 */
void	free_vector(t_vector *vec)
{
	if (!vec)
		return ;
	if (vec->array)
		free(vec->array);
	vec->array = NULL;
	vec->allocated = 0;
	vec->size = 0;
}
