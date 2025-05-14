/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:28:47 by willda-s          #+#    #+#             */
/*   Updated: 2024/11/20 23:49:27 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst->content)
		del(lst->content);
	if (lst)
		free(lst);
}
/*
int	main(void)
{
	t_list *aa;
	t_list *bb;

	bb = ft_lstnew(NULL);
	aa = ft_lstnew(NULL);
	aa->next = bb;
	printf("%p\n", ft_lstlast(aa));
	printf("%p", bb);
}*/