/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:14:13 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/08 00:53:46 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_expand_err(char *word, t_data *data)
{
	if (!word || !word[data->i])
		return (2);
	if (word && word[data->i] == '?')
	{
		data->i++;
		return (1);
	}
	if (!word[data->i] || (!is_var_char(word[data->i]) && word[data->i] != '"'
			&& word[data->i] != '\''))
		return (2);
	return (0);
}

static void	get_var_name(char *word, t_data *data, char *var)
{
	int	k;

	k = 0;
	while (word[data->i] && is_var_char(word[data->i]) && word[data->i] != '"'
		&& word[data->i] != '\'' && k < 255)
		var[k++] = word[(data->i)++];
	var[k] = '\0';
}

static int	copy_env_value(char *res, int j, char *val)
{
	int	k;

	k = 0;
	while (val && val[k])
		res[j++] = val[k++];
	return (j);
}

int	ft_expand_var(char *res, int j, char *word, t_data *data)
{
	char	var[256];
	char	*val;
	int		err;

	data->i++;
	err = is_expand_err(word, data);
	if (err == 1)
		return (handle_errcode(res, j));
	if (err == 2)
	{
		res[j++] = '$';
		return (j);
	}
	get_var_name(word, data, var);
	val = get_env_value(data->env, var);
	j = copy_env_value(res, j, val);
	return (j);
}
