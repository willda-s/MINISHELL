/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:36:33 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 18:38:26 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

/**
 * at_vector - Returns a pointer to the element at the specified index
 * @vec: Pointer to the vector structure
 * @i: Index of the element to access
 * 
 * This function provides direct access to an element in the vector by
 * calculating its memory address based on the index and element size.
 * It performs pointer arithmetic to locate the exact position of the
 * requested element within the vector's data array.
 * 
 * Note: This function does not perform bounds checking. The caller is
 * responsible for ensuring the index is within valid range (0 <= i < size).
 * 
 * Return: Pointer to the element at index i, or undefined behavior if
 *         index is out of bounds
 */
void	*at_vector(t_vector *vec, size_t i)
{
	return (vec->array + i * vec->elemsize);
}
