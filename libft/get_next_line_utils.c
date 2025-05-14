/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:57:43 by willda-s          #+#    #+#             */
/*   Updated: 2025/04/25 19:11:23 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strccpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strrlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	if (str && str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjjoin(char *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strrlen(s1) + ft_strrlen(s2);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2 && *s2 && *s2 != '\n')
	{
		dest[i] = *s2;
		i++;
		s2++;
	}
	if (s2 && *s2 == '\n')
		dest[i++] = '\n';
	dest[i] = '\0';
	return (free(s1), dest);
}

int	ft_strcchr(const char *str, int c)
{
	int				i;
	unsigned char	tmp;

	i = 0;
	tmp = (unsigned char)c;
	while (str && str[i])
	{
		if (tmp == (unsigned char)str[i])
			return (i + 1);
		i++;
	}
	if (tmp == '\0')
		return (i + 1);
	return (-1);
}
