/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:56:04 by willda-s          #+#    #+#             */
/*   Updated: 2024/11/27 17:24:13 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list) * 1);
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
int	main(void)
{
	t_list *slt;
	slt = ft_lstnew((void *)"new");
	slt->next = ft_lstnew((void *)"Slt");
	printf("%p", (char *)slt->next);
	free(slt->next);
	free(slt);
}*/