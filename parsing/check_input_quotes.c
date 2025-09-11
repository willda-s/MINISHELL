/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:18:58 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/10 20:21:18 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

char	*allocate_and_initialize(char *input, size_t *new_len)
{
	char	*new_input;

	*new_len = calculate_new_len(input);
	new_input = malloc(sizeof(char) * (*new_len + 1));
	if (!new_input)
		return (NULL);
	return (new_input);
}

int	update_quote_state(char c, int current_state)
{
	if (c == '\'' && current_state != 2)
	{
		if (current_state == 1)
			return (0);
		return (1);
	}
	if (c == '\"' && current_state != 1)
	{
		if (current_state == 2)
			return (0);
		return (2);
	}
	return (current_state);
}
