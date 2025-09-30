/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:36:47 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/29 23:38:16 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "signals.h"

int	is_expand_err(char *word, t_data *data)
{
	if (!word || !word[data->i])
		return (2);
	if (word && word[data->i] == '$')
	{
		data->i++;
		return (3);
	}
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

int	handle_errcode(char *res, int j)
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
