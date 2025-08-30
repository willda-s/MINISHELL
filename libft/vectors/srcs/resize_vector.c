/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:40:45 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 18:46:39 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vectors.h"

/**
 * resize_vector - Reallocates memory for the vector to accommodate new capacity
 * @vec: Pointer to the vector structure to resize
 * 
 * This function allocates a new memory block with the vector's current
 * allocated capacity and copies all existing data to the new location.
 * The remaining space in the new allocation is zero-initialized.
 * 
 * The function safely handles the memory transition by:
 * 1. Allocating new memory based on vec->allocated * vec->elemsize
 * 2. Copying existing data from old to new memory
 * 3. Zero-filling the remaining space
 * 4. Freeing the old memory block
 * 5. Updating the vector's array pointer
 * 
 * Return: 0 on successful resize, -1 if memory allocation fails
 */
int	resize_vector(t_vector *vec)
{
	size_t	elem;
	void	*ptr;

	elem = vec->size * vec->elemsize;
	ptr = malloc(vec->allocated * vec->elemsize);
	if (ptr == NULL)
		return (-1);
	ft_memcpy(ptr, vec->array, elem);
	ft_memset(ptr + elem, 0, (vec->allocated * vec->elemsize) - elem);
	if (vec->array)
		free(vec->array);
	vec->array = ptr;
	return (0);
}
