/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:functions_free.c
/*   Created: 2025/08/03 07:10:30 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/27 20:20:54 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "fd_printf.h"
=======
/*   Created: 2024/11/13 14:34:11 by willda-s          #+#    #+#             */
/*   Updated: 2024/11/28 18:52:47 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
>>>>>>> cam:libft/ft_calloc.c

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (SIZE_MAX / nmemb < size)
		return (NULL);
	tmp = malloc(nmemb * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, nmemb * size);
	return (tmp);
}
/*
int	main(void)
{
	int *tab;
	int i;

	i = 0;
	tab = ft_calloc(5, 1);
	while (i < 5)
	{
		printf("%c", tab[i]);
		i++;
	}
<<<<<<< HEAD:functions_free.c
	free(dst);
}

int	free_all(t_data *data, int errcode, char *str)
{
	if (data->env)
		free_lst_env(&data->env, false, 0);
	if (data->pars)
		free_lst_pars(&data->pars);
	if (data->exec)
		free_lst_exec(&data->exec);
	if (data->envp)
		free_tab(data->envp);
	if (data->dst)
		free_tab(data->dst);
	ft_dprintf(2, "%s\n",str);
	exit(errcode);
}
=======
	return (0);
}*/
>>>>>>> cam:libft/ft_calloc.c
