/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:libft/libft_functions/srcs/ft_strndup.c
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libft/libft_functions/srcs/ft_strndup.c
/*   Created: 2025/08/27 19:59:29 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/27 20:01:48 by akarapkh         ###   ########.fr       */
=======
/*   Created: 2024/11/14 13:17:01 by willda-s          #+#    #+#             */
/*   Updated: 2025/06/30 14:05:21 by willda-s         ###   ########.fr       */
>>>>>>> cam:libft/ft_strjoin.c
========
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 07:10:55 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 14:19:55 by akarapkh         ###   ########.fr       */
>>>>>>>> parsing:libft/libft_functions/srcs/ft_strdup.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<<< HEAD:libft/libft_functions/srcs/ft_strndup.c
char	*ft_strndup(const char *str, size_t len)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
========
char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (s[src_len])
		src_len++;
	dest = malloc(sizeof(char) * (src_len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
>>>>>>>> parsing:libft/libft_functions/srcs/ft_strdup.c
}
