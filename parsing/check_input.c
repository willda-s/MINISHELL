/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:18:26 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/31 18:58:02 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

static char	*dup_with_new_len(char *input, size_t new_len);
static int	is_command(char cmd);
static int	is_space(char c);

char	*check_input(char *input)
{
	size_t	new_len;
	char	*result;

	if (!input)
		return (0);
	new_len = ft_strlen(input);
	result = dup_with_new_len(input, new_len);
	return (result);
}

static char	*dup_with_new_len(char *input, size_t new_len)
{
	char	*new_input;

	new_input = ft_memmove(new_input, input, new_len + 1);
	input = NULL;
	return (new_input);
}

static char	*add_space(char *input)
{
	size_t	i;
	char	*new_input;

	i = 0;
	new_input = malloc(sizeof(char) * (new_len + 1));
	if (!new_input)
		return (NULL);
	while (input[i])
	{
		if (is_command(input[i]))
		{
		}
	}
}

static int	calculate_new_len(char *new_input)
{
	size_t	i;
	size_t	new_len;

	i = 0;
	new_len = ft_strlen(new_input);
	while (new_input[i])
	{
		if (is_command(new_input[i]) == 1)
		{
			if (new_input[i] && !is_space(new_input[i + 1]))
			{
				if (i != 0 && !is_space(new_input[i - 1]))
					++new_len;
				++new_len;
			}
		}
		else if (is_command(new_input[i]) == 2)
		{
			if (ft_strcmp(&new_input[i], &new_input[i + 1]))
				++i;
			if (new_input[i] && !is_space(new_input[i + 1]))
			{
			}
		}
		if (is_command(new_input[i]) == 3)
	}
}

static int	is_command(char cmd)
{
	if (cmd == '|')
		return (1);
	if (cmd == '<')
		return (2);
	if (cmd == '>')
		return (3);
	return (0);
}

static int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	main(int ac, char **av)
{
	char	*result;

	// size_t	space_count;
	// size_t	i;
	result = NULL;
	// i = 0;
	// space_count = 0;
	if (ac == 2)
	{
		result = check_input(av[1]);
		// while (result[i])
		// {
		// 	if (ft_strcmp(&result[i], " ") == 0)
		// 		++space_count;
		// 	++i;
		// }
		// printf("count =%zu\n", space_count);
		printf("%s\n", result);
	}
	return (0);
}
