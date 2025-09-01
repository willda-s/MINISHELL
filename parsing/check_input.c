/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:18:26 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/01 19:52:08 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*add_space(char *input);
static void	add_space_to_pipe(char *input, char *new_input, size_t *i,
				size_t *j);
static void	add_space_to_redir(char *input, char *new_input, size_t *i,
				size_t *j);

char	*check_input(char *input)
{
	char	*result;

	if (!input)
		return (0);
	result = add_space(input);
	if (!result)
		return (NULL);
	return (result);
}

static char	*add_space(char *input)
{
	size_t	i;
	size_t	j;
	size_t	new_len;
	char	*new_input;

	new_len = calculate_new_len(input);
	new_input = malloc(sizeof(char) * (new_len + 1));
	if (!new_input)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (is_command(input[i]) == 1)
			add_space_to_pipe(input, new_input, &i, &j);
		else if (is_command(input[i]) == 2 || is_command(input[i]) == 3)
			add_space_to_redir(input, new_input, &i, &j);
		else
			new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
	return (new_input);
}

static void	add_space_to_pipe(char *input, char *new_input, size_t *i,
		size_t *j)
{
	if ((*i) != 0 && !is_space(input[(*i) - 1]))
		new_input[(*j)++] = ' ';
	new_input[(*j)++] = input[(*i)++];
	if (input[(*i)] && !is_space(input[(*i)]))
		new_input[(*j)++] = ' ';
}

static void	add_space_to_redir(char *input, char *new_input, size_t *i,
		size_t *j)
{
	if (is_command(input[(*i)]) == 2)
	{
		if ((*i) != 0 && !is_space(input[(*i) - 1]))
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[(*i)++];
		if (input[(*i)] && input[(*i)] == '<')
			new_input[(*j)++] = input[(*i)++];
		if (input[(*i)] && !is_space(input[(*i)]))
			new_input[(*j)++] = ' ';
	}
	else if (is_command(input[(*i)]) == 3)
	{
		if ((*i) != 0 && !is_space(input[(*i) - 1]))
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[(*i)++];
		if (input[(*i)] && input[(*i)] == '>')
			new_input[(*j)++] = input[(*i)++];
		if (input[(*i)] && !is_space(input[(*i)]))
			new_input[(*j)++] = ' ';
	}
}
