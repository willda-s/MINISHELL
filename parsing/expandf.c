/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:32 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 20:11:50 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stddef.h>
#include <stdlib.h>

static int	ft_handle_squotes(char *res, int j, char *word, t_data *data)
{
	size_t	word_len;

	word_len = ft_strlen(word);
	data->i++;
	while (word[data->i] && word[data->i] != '\'')
		res[j++] = word[data->i++];
	if (word[data->i] == '\'' && data->i < word_len)
		data->i++;
	else
	{
		syntax_error(SIMPLE_QUOTE);
		data->syntax_error_flag = 1;
		return (-1);
	}
	return (j);
}

static int	ft_handle_dquotes(char *res, int j, char *word, t_data *data)
{
	size_t	word_len;

	word_len = ft_strlen(word);
	data->i++;
	while (word[data->i] && word[data->i] != '"')
	{
		if (word[data->i] == '$')
			j = ft_expand_var(res, j, word, data);
		else
			res[j++] = word[data->i++];
	}
	if (word[data->i] == '"' && data->i < word_len)
		data->i++;
	else
	{
		data->syntax_error_flag = 1;
		syntax_error(DOUBLE_QUOTE);
		return (-1);
	}
	return (j);
}

static int	max_len_in_env(t_env *env)
{
	size_t	len;

	len = 0;
	while (env)
	{
		if (ft_strlen(env->value) > len)
			len = ft_strlen(env->value);
		if (ft_strlen(env->key) > len)
			len = ft_strlen(env->key);
		env = env->next;
	}
	return (len);
}

static int	handle_quote_or_dollar(char *word, char *res, ssize_t j,
		t_data *data)
{
	if (word[data->i] == '\'')
		j = ft_handle_squotes(res, j, word, data);
	else if (word[data->i] == '"')
		j = ft_handle_dquotes(res, j, word, data);
	else if (word[data->i] == '$')
		j = ft_expand_var(res, j, word, data);
	return (j);
}

static int	process_expansion(char *word, char *res, t_data *data)
{
	ssize_t	j;
	ssize_t	max_len;

	j = 0;
	data->i = 0;
	max_len = ft_strlen(word) + max_len_in_env(data->env);
	while (word[data->i])
	{
		j = handle_quote_or_dollar(word, res, j, data);
		if (j < 0 || j >= max_len)
			return (-1);
		if (!word[data->i])
			break ;
		if (word[data->i] != '\'' && word[data->i] != '"'
			&& word[data->i] != '$')
			res[j++] = word[data->i++];
	}
	res[j] = '\0';
	return (j);
}

char	*ft_expand_word(t_data *data, char *word)
{
	ssize_t	max_len;
	char	*res;
	char	*dup;

	max_len = ft_strlen(word) + max_len_in_env(data->env);
	res = malloc(max_len + 1);
	if (!res)
		return (NULL);
	if (process_expansion(word, res, data) < 0)
	{
		free(res);
		return (NULL);
	}
	dup = ft_strdup(res);
	if (!dup)
		return (NULL);
	free(res);
	return (dup);
}

bool	is_only_dollars(char *word)
{
	int	i;

	i = 0;
	while (word && word[i])
	{
		if (word[i] != '$')
			return (false);
		i++;
	}
	return (true);
}
