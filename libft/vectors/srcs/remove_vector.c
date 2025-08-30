/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:42:00 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 18:46:04 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vectors.h"

/**
 * remove_vector - Removes an element from the vector at the specified index
 * @vec: Pointer to the vector structure
 * @i: Index of the element to remove
 * 
 * This function removes an element from the vector by shifting all subsequent
 * elements down by one position to fill the gap. It performs bounds checking
 * to ensure the index is valid before attempting the removal.
 * 
 * The function calculates the number of elements that need to be moved and
 * uses ft_memmove to safely shift the memory, handling potential overlap
 * between source and destination regions.
 * 
 * After removal, the vector size is decremented by one. The allocated
 * capacity remains unchanged.
 */
void	remove_vector(t_vector *vec, size_t i)
{
	const size_t	rmi = i * vec->elemsize;
	const size_t	remaining_elements = vec->size - i - 1;
	const size_t	bytes_to_move = remaining_elements * vec->elemsize;
	void			*rmptr;

	if (!vec || i >= vec->size)
		return ;
	rmptr = vec->array + rmi;
	if (remaining_elements > 0)
		ft_memmove(rmptr, rmptr + vec->elemsize, bytes_to_move);
	vec->size--;
}
