/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:32 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/25 18:52:00 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stddef.h>

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
	{
		// 	if (j == 0 && ft_strlen(word) == 3)
		// 		res[j++] = '$';
		data->i++;
	}
	else
	{
		syntax_error(DOUBLE_QUOTE);
		return (-1);
	}
	return (j);
}

int	max_len_in_env(t_env *env)
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

char	*ft_expand_word(t_data *data, char *word)
{
	size_t	max_len;
	char	*res;
	char	*dup;
	size_t	j;

	max_len = ft_strlen(word) + max_len_in_env(data->env);
	res = malloc(max_len + 1);
	if (!res)
		return (NULL);
	j = 0;
	data->i = 0;
	while (word[data->i])
	{
		if (word[data->i] == '\'')
			j = ft_handle_squotes(res, j, word, data);
		else if (word[data->i] == '"')
			j = ft_handle_dquotes(res, j, word, data);
		else if (word[data->i] == '$')
			j = ft_expand_var(res, j, word, data);
		if (j < 0 || j >= max_len)
		{
			free(res);
			return (NULL);
		}
		if (!word[data->i])
			break ;
		if (word[data->i] != '\'' && word[data->i] != '"'
			&& word[data->i] != '$')
			res[j++] = word[data->i++];
	}
	res[j] = '\0';
	dup = ft_strdup(res);
	if (!dup)
		return (NULL);
	free(res);
	return (dup);
}

int	expand_exec_list(t_data *data)
{
	char	*new_word;
	t_exec	*exec;
	int		i;

	exec = data->exec;
	while (exec)
	{
		i = -1;
		while (exec->cmd && exec->cmd[++i])
		{
			new_word = ft_expand_word(data, exec->cmd[i]);
			if (new_word)
			{
				free(exec->cmd[i]);
				exec->cmd[i] = new_word;
			}
			else
			{
				free_tmpall(data);
				return (2);
			}
		}
		exec = exec->next;
	}
	return (0);
}
