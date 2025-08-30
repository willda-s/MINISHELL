/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:18:26 by akarapkh          #+#    #+#             */
/*   Updated: 2025/08/30 18:57:27 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_new_len(char *input);
static char	*dup_with_new_len(char *input, size_t new_len);

char	*check_input(char *input)
{
	size_t	new_len;

	if (!input)
		return (0);
	new_len = get_new_len(input);
	dup_with_new_len(input, new_len);
}

static char	*dup_with_new_len(char *input, size_t new_len)
{
	char	*new_input;

	new_input = malloc(sizeof(char) * (new_len + 1));
	ft_memmove(new_input, input, new_len + 1);
	free(input);
	input = NULL;

	return (new_input);
}

static size_t	get_new_len(char *input)
{
	size_t i;
	size_t input_len;

	input_len = ft_strlen(input);
	i = 0;
	while (input[i])
	{
		if (ft_strncmp(&input[i], "|", 1))
		{
			++input_len;
		}
		++i;
	}
	return (i + input_len);
}