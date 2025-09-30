/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_extract.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:39:38 by cafabre           #+#    #+#             */
/*   Updated: 2025/10/01 00:07:07 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static char	*extract_key(char *cmd_arg)
{
	int		i;
	char	*key;

	i = 0;
	key = malloc(ft_strlen(cmd_arg) + 1);
	if (!key)
		return (NULL);
	while (cmd_arg[i] && cmd_arg[i] != '=')
	{
		key[i] = cmd_arg[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static char	*extract_value(char *cmd_arg)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = malloc(ft_strlen(cmd_arg) + 1);
	if (!value)
		return (NULL);
	while (cmd_arg[i] && cmd_arg[i] != '=')
		i++;
	if (cmd_arg[i] == '=')
		i++;
	while (cmd_arg[i])
		value[j++] = cmd_arg[i++];
	value[j] = '\0';
	return (value);
}

t_env	*extract_key_value(t_exec *exec, size_t index)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = extract_key(exec->cmd[index]);
	if (!env->key)
	{
		free(env);
		return (NULL);
	}
	if (ft_strchr(exec->cmd[index], '='))
	{
		env->value = extract_value(exec->cmd[index]);
		if (!env->value)
		{
			free(env->key);
			free(env);
			return (NULL);
		}
	}
	else
		env->value = NULL;
	env->next = NULL;
	return (env);
}
