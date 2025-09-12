/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:18:26 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/12 17:27:14 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static char	*add_space(char *input);
static void	process_character(t_process_data *data, size_t *i, size_t *j);
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
	size_t			i;
	size_t			j;
	t_process_data	data;

	data.input = input;
	data.new_input = allocate_and_initialize(data.input, &data.new_len);
	if (!data.new_input)
		return (NULL);
	i = 0;
	j = 0;
	data.quote_state = 0;
	while (data.input[i])
		process_character(&data, &i, &j);
	data.new_input[j] = '\0';
	return (data.new_input);
}

static void	process_character(t_process_data *data, size_t *i, size_t *j)
{
	data->quote_state = update_quote_state(data->input[*i], data->quote_state);
	if (data->quote_state == 0)
	{
		if (is_command(data->input[*i]) == 1)
			add_space_to_cmd(data->input, data->new_input, i, j);
		else if (is_command(data->input[*i]) == 2
			|| is_command(data->input[*i]) == 3)
			add_space_to_redir(data->input, data->new_input, i, j);
		else
			data->new_input[(*j)++] = data->input[(*i)++];
	}
	else
		data->new_input[(*j)++] = data->input[(*i)++];
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
