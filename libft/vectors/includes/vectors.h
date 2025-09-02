/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:43:34 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/09 19:22:52 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BASE_ALLOC
#  define BASE_ALLOC 64
# endif

typedef struct s_vector
{
	size_t	elemsize;
	size_t	size;
	size_t	allocated;
	void	*array;

}			t_vector;

void		free_vector(t_vector *vec);
void		*at_vector(t_vector *vec, size_t i);
void		remove_vector(t_vector *vec, size_t i);
void		init_vector(t_vector *vec, size_t elemsize);
void		set_alloc_size(t_vector *vec, size_t count);
int			resize_vector(t_vector *vec);
int			dup_vector(t_vector *src, t_vector *dst);
int			reserve_vector(t_vector *vector, size_t size);
int			merge_vector(t_vector *from, t_vector *to, size_t i);
int			add_vector(t_vector *vec, const void *data, size_t count);
int			set_value_at_vector(t_vector *vec, const void *data, size_t i);

#endif