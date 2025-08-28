/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:09:01 by willda-s          #+#    #+#             */
/*   Updated: 2024/11/20 23:45:03 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	t_list *aa;
	t_list *bb;

	bb = ft_lstnew(NULL);
	bb->next = NULL;
	aa = ft_lstnew(NULL);
	aa->next = bb;
	printf("%d", ft_lstsize(aa));
}*/