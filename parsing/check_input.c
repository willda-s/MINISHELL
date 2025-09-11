/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:18:26 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/11 14:44:51 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static int	*fill_new_input(char *input, char *new_input);
static char	*add_space(char *input);
static void	add_space_to_cmd(char *input, char *new_input, size_t *i,
								size_t *j);
static void	add_space_to_redir(char *input, char *new_input, size_t *i,
								size_t *j);
static int	update_quote_state(char c, int current_state);

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

static int	*fill_new_input(char *input, char *new_input)
{
	size_t	i;
	size_t	j;
	int		quote_state;

	i = 0;
	j = 0;
	quote_state = 0;
	new_input = add_space(input);
	while (input[i])
	{
		quote_state = update_quote_state(input[i], quote_state);
		if (quote_state == 0)
		{
			if (is_command(input[i]) == 1)
				add_space_to_cmd(input, new_input, &i, &j);
			else if (is_command(input[i]) == 2 || is_command(input[i]) == 3)
				add_space_to_redir(input, new_input, &i, &j);
			else
				new_input[j++] = input[i++];
		}
		new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
	return (EXIT_SUCCESS);
}

static char	*add_space(char *input)
{
	size_t	new_len;
	char	*new_input;

	new_len = calculate_new_len(input);
	new_input = malloc(sizeof(char) * (new_len + 1));
	if (!new_input)
		return (NULL);
	fill_new_input(input, new_input);
	return (new_input);
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

static int update_quote_state(char c, int current_state)
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
