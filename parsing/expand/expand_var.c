/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:14:13 by akarapkh          #+#    #+#             */
/*   Updated: 2025/10/01 00:27:41 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static void		get_var_name(char *word, t_data *data, char *var);
static size_t	get_var_name_len(char *word, int start_pos);
static int		copy_env_value(char *res, int j, char *val);

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
	if (err == 3)
		return (j);
	if (err == 2)
	{
		res[j++] = '$';
		return (j);
	}
	var_len = get_var_name_len(word, data->i);
	var = malloc(var_len + 1);
	if (!var)
		return (j);
	get_var_name(word, data, var);
	val = get_env_value(data->env, var);
	j = copy_env_value(res, j, val);
	free(var);
	return (j);
}

static size_t	get_var_name_len(char *word, int start_pos)
{
	size_t	len;
	int		i;

	len = 0;
	i = start_pos;
	while (word[i] && is_var_char(word[i]) && word[i] != '"' && word[i] != '\'')
	{
		len++;
		i++;
	}
	return (len);
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
		return (j);
	while (val && val[k])
		res[j++] = val[k++];
	return (j);
}
