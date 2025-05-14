/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamguerreiro <williamguerreiro@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:37:18 by willda-s          #+#    #+#             */
/*   Updated: 2025/05/11 18:27:05 by williamguer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_word(char const *s, char c)
{
	size_t	i;
	size_t	j;
	bool	inword;

	i = 0;
	j = 0;
	inword = false;
	while (s[i])
	{
		if (s[i] == c)
			inword = false;
		if (s[i] != c && !inword)
		{
			inword = true;
			j++;
		}
		i++;
	}
	return (j);
}

static int	ft_strlenword(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_strndup(const char *str, size_t len)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static void	*ft_free(char **s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	length;
	char	**dst;

	i = 0;
	j = 0;
	dst = ft_calloc(count_word(s, c) + 1, sizeof(char *));
	if (!dst)
		return (NULL);
	while (s[j])
	{
		while (s[j] == c && s[j])
			j++;
		if (s[j] != c && s[j])
		{
			length = ft_strlenword(&s[j], c);
			dst[i] = ft_strndup(&s[j], length);
			if (!dst[i])
				return (ft_free(dst, i));
			i++;
			j += length;
		}
	}
	return (dst);
}

/*
int	main(void)
{
	char *s;
	char **str;
	size_t	i;

	i = 0;
	s = "bonjour comment va";
	str = ft_split(s, ' ');
	while(str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	ft_free(str, i);

}*/