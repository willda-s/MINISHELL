/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:18:26 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/10 20:22:26 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static char	*add_space(char *input);
static void	process_character(char *input, char *new_input, size_t *i,
				size_t *j, int *quote_state);
static void	add_space_to_cmd(char *input, char *new_input, size_t *i,
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
	int		quote_state;

	new_input = allocate_and_initialize(input, &new_len);
	if (!new_input)
		return (NULL);
	i = 0;
	j = 0;
	quote_state = 0;
	while (input[i])
	{
		process_character(input, new_input, &i, &j, &quote_state);
	}
	new_input[j] = '\0';
	return (new_input);
}

static void	process_character(char *input, char *new_input, size_t *i,
		size_t *j, int *quote_state)
{
	*quote_state = update_quote_state(input[*i], *quote_state);
	if (*quote_state == 0)
	{
		if (is_command(input[*i]) == 1)
			add_space_to_cmd(input, new_input, i, j);
		else if (is_command(input[*i]) == 2 || is_command(input[*i]) == 3)
			add_space_to_redir(input, new_input, i, j);
		else
			new_input[(*j)++] = input[(*i)++];
	}
	else
		new_input[(*j)++] = input[(*i)++];
}

static void	add_space_to_cmd(char *input, char *new_input, size_t *i, size_t *j)
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
