/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandf_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 02:56:30 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/30 03:09:06 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

int	ft_handle_squotes(char *res, int j, char *word, t_data *data)
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

int	ft_handle_dquotes(char *res, int j, char *word, t_data *data)
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

static char	*process_word_expansion(t_exec *exec, t_data *data, int i)
{
	char	*new_word;

	if (is_only_dollars(exec->cmd[i]))
	{
		new_word = ft_strdup(exec->cmd[i]);
		if (!new_word)
			free_all_msg(data, 12, "Malloc fail in expand_exec_list");
	}
	else
		new_word = ft_expand_word(data, exec->cmd[i]);
	return (new_word);
}

static int	expand_single_word(t_exec *exec, t_data *data, int i)
{
	char	*new_word;

	new_word = process_word_expansion(exec, data, i);
	if (data->syntax_error_flag)
	{
		free_tmpall(data);
		return (2);
	}
	else if (new_word)
	{
		free(exec->cmd[i]);
		exec->cmd[i] = new_word;
	}
	else
	{
		free(exec->cmd[i]);
		exec->cmd[i] = ft_strdup("");
		if (!exec->cmd[i])
		{
			free_tmpall(data);
			return (127);
		}
	}
	return (0);
}

int	expand_exec_list(t_data *data)
{
	t_exec	*exec;
	int		i;
	int		ret;

	exec = data->exec;
	while (exec)
	{
		i = -1;
		while (exec->cmd && exec->cmd[++i])
		{
			ret = expand_single_word(exec, data, i);
			if (ret != 0)
				return (ret);
		}
		exec = exec->next;
	}
	return (0);
}
