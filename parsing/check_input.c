/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:18:26 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/01 18:54:59 by akarapkh         ###   ########.fr       */
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

// static size_t	calculate_new_len(char *input)
// {
// 	size_t	i;
// 	size_t	new_len;

// 	i = 0;
// 	new_len = ft_strlen(input);
// 	while (input[i])
// 	{
// 		if (is_command(input[i]) == 1)
// 		{
// 			if (i > 0 && !is_space(input[i - 1]))
// 				++new_len;
// 			if (input[i] && !is_space(input[i + 1]))
// 				++new_len;
// 		}
// 		else if (is_command(input[i]) == 2)
// 		{
// 			if (i > 0 && !is_space(input[i - 1]))
// 				++new_len;
// 			if (input[i + 1] && (input[i] == input[i + 1]))
// 				++i;
// 			if (input[i] && !is_space(input[i + 1]))
// 				++new_len;
// 		}
// 		else if (is_command(input[i]) == 3)
// 		{
// 			if (i > 0 && !is_space(input[i - 1]))
// 				++new_len;
// 			if (input[i + 1] && (input[i] == input[i + 1]))
// 				++i;
// 			if (input[i] && !is_space(input[i + 1]))
// 				++new_len;
// 		}
// 		++i;
// 	}
// 	return (new_len);
// }

// int	main(int ac, char **av)
// {
// 	char	*result;

// 	// size_t	space_count;
// 	// size_t	i;
// 	result = NULL;
// 	// i = 0;
// 	// space_count = 0;
// 	if (ac == 2)
// 	{
// 		result = check_input(av[1]);
// 		// while (result[i])
// 		// {
// 		// 	if (ft_strcmp(&result[i], " ") == 0)
// 		// 		++space_count;
// 		// 	++i;
// 		// }
// 		// printf("count =%zu\n", space_count);
// 		printf("%s\n", result);
// 	}
// 	return (0);
// }
