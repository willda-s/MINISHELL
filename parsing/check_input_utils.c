/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:42:46 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/03 17:26:40 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static void	handle_double_cmd(char *input, size_t *i, size_t *new_len);
static void	handle_single_cmd(char *input, size_t *i, size_t *new_len);

int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	is_command(char cmd)
{
	if (cmd == '|')
		return (1);
	if (cmd == '<')
		return (2);
	if (cmd == '>')
		return (3);
	if (cmd == '(')
		return (1);
	if (cmd == ')')
		return (1);
	if (cmd == '\\')
		return (1);
	return (0);
}

size_t	calculate_new_len(char *input)
{
	size_t	i;
	size_t	new_len;

	i = 0;
	new_len = ft_strlen(input);
	while (input[i])
	{
		if (is_command(input[i]) == 1)
			handle_single_cmd(input, &i, &new_len);
		else if (is_command(input[i]) == 2)
			handle_double_cmd(input, &i, &new_len);
		else if (is_command(input[i]) == 3)
			handle_double_cmd(input, &i, &new_len);
		++i;
	}
	return (new_len);
}

static void	handle_double_cmd(char *input, size_t *i, size_t *new_len)
{
	if (*i > 0 && !is_space(input[*i - 1]))
		++(*new_len);
	if (input[*i + 1] && (input[*i] == input[*i + 1]))
		++(*i);
	if (input[*i] && !is_space(input[*i + 1]))
		++(*new_len);
}

static void	handle_single_cmd(char *input, size_t *i, size_t *new_len)
{
	if (*i > 0 && !is_space(input[*i - 1]))
		++(*new_len);
	if (input[*i] && !is_space(input[*i + 1]))
		++(*new_len);
}
