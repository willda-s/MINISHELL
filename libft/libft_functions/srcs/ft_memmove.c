/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:libft/libft_functions/srcs/ft_lstclear_bonus.c
/*   Created: 2024/11/20 04:56:37 by akarapkh          #+#    #+#             */
========
/*   Created: 2024/11/14 07:33:16 by akarapkh          #+#    #+#             */
>>>>>>>> parsing:libft/libft_functions/srcs/ft_memmove.c
/*   Updated: 2025/06/28 14:19:55 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<<< HEAD:libft/libft_functions/srcs/ft_lstclear_bonus.c
void	ft_lstclear(t_list **lst, void (*del)(int))
{
	t_list	*current;
	t_list	*next_node;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next_node = current->next;
		del(current->content);
		free(current);
		current = next_node;
	}
	*lst = NULL;
========
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const long int	diff = dest - src;
	size_t			i;

	if (diff > 0)
	{
		while (n > 0)
		{
			--n;
			((char *)(dest))[n] = ((char *)(src))[n];
		}
	}
	else if (diff < 0)
	{
		i = 0;
		while (i < n)
		{
			((char *)(dest))[i] = ((char *)(src))[i];
			++i;
		}
	}
	return (dest);
>>>>>>>> parsing:libft/libft_functions/srcs/ft_memmove.c
}
