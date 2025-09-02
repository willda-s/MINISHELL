/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libft/ft_calloc.c
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
=======
/*   Created: 2024/11/15 07:32:24 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 14:19:55 by akarapkh         ###   ########.fr       */
>>>>>>> parsing:libft/libft_functions/srcs/ft_calloc.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
>>>>>>> cam:libft/ft_calloc.c

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	total_size;

	total_size = nmemb * size;
	if (total_size == 0)
	{
		res = malloc(0);
		return (res);
	}
<<<<<<< HEAD:libft/ft_calloc.c
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
=======
	if (total_size / size != nmemb)
		return (NULL);
	res = malloc(total_size);
	if (!res)
		return (NULL);
	ft_memset(res, 0, total_size);
	return (res);
}
>>>>>>> parsing:libft/libft_functions/srcs/ft_calloc.c
