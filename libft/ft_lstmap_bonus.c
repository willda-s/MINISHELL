/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 01:22:17 by willda-s          #+#    #+#             */
/*   Updated: 2024/11/27 17:21:36 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*tmp;
	void	*tmp_content;

	first = NULL;
	while (lst)
	{
		tmp_content = f(lst->content);
		if (!tmp_content)
			return (ft_lstclear(&first, del), NULL);
		tmp = ft_lstnew(tmp_content);
		if (!tmp)
			return (del(tmp_content), ft_lstclear(&first, del), NULL);
		ft_lstadd_back(&first, tmp);
		lst = lst->next;
	}
	return (first);
}
