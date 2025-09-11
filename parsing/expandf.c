/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:32 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/11 19:03:46 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static int	ft_handle_squotes(char *res, int j, char *word, t_data *data)
{
	data->i++;
	while (word[data->i] && word[data->i] != '\'')
		res[j++] = word[data->i++];
	if (word[data->i] == '\'')
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
	data->i++;
	while (word[data->i] && word[data->i] != '"')
	{
		if (word[data->i] == '$')
			j = ft_expand_var(res, j, word, data);
		else
			res[j++] = word[data->i++];
	}
	if (word[data->i] == '"')
	{
		if (j == 0 && ft_strlen(word) == 3)
			res[j++] = '$';
		data->i++;
	}
	else
	{
		syntax_error(DOUBLE_QUOTE);
		return (-1);
	}
	return (j);
}

static char	*ft_expand_word(t_data *data, char *word)
{
	char	res[4096];
	int		j;

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
		if (j == -1)
			return (NULL);
		if (word[data->i] != '\'' && word[data->i] != '"'
			&& word[data->i] != '$')
			res[j++] = word[data->i++];
	}
	res[j] = '\0';
	return (ft_strdup(res));
}

int	expand_exec_list(t_data *data)
{
	char	*new_word;
	t_exec	*exec;
	int		i;

	exec = data->exec;
	while (exec)
	{
		i = 0;
		while (exec->cmd && exec->cmd[i])
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
			i++;
		}
		exec = exec->next;
	}
	return (0);
}
