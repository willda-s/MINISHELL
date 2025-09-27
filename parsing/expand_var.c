/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:14:13 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/27 05:29:40 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "signals.h"
#include <stddef.h>
#include <stdlib.h>

static int	is_expand_err(char *word, t_data *data)
{
	if (!word || !word[data->i])
		return (2);
	if (word && word[data->i] == '?')
	{
		data->i++;
		return (1);
	}
	if (word[data->i] == '"' || word[data->i] == '\'')
		return (2);
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
	if (!val || (val == (char *)1))
		return (-1);
	while (val && val[k])
		res[j++] = val[k++];
	return (j);
}

static int	handle_errcode(char *res, int j)
{
	char	*str;
	size_t	i;
	size_t	len;

	str = ft_itoa(g_signal_status);
	if (!str)
		return (j);
	len = ft_strlen(str);
	i = 0;
	while (i < len)
		res[j++] = str[i++];
	free(str);
	return (j);
}

int	ft_expand_var(char *res, int j, char *word, t_data *data)
{
	char	*var;
	char	*val;
	int		err;
	size_t	var_len;

	data->i++;
	err = is_expand_err(word, data);
	if (err == 1)
		return (handle_errcode(res, j));
	if (err == 2)
	{
		res[j++] = '$';
		return (j);
	}
	var_len = max_len_in_env(data->env);
	var = malloc(var_len + 1);
	if (!var)
		return (j);
	get_var_name(word, data, var);
	val = get_env_value(data->env, var);
	j = copy_env_value(res, j, val);
	free(var);
	return (j);
}
