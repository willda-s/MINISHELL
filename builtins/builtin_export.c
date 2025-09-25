/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:08 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/25 04:28:11 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "parsing.h"
#include <stdio.h>

static int	parsing_export(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->cmd && exec->cmd[1][i] && exec->cmd[1][i] != '=')
	{
		if (!ft_isalnum(exec->cmd[1][i]) && exec->cmd[1][i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static char	*extract_key(char *cmd_arg)
{
	int		i;
	char	*key;

	i = 0;
	key = malloc(ft_strlen(cmd_arg) + 1);
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

static t_env	*extract_key_value(t_exec *exec)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = extract_key(exec->cmd[1]);
	env->value = extract_value(exec->cmd[1]);
	env->next = NULL;
	return (env);
}

int	builtin_export(t_exec *exec, t_data *data)
{
	t_env	*new_var;
	t_env	*tmp;

	tmp = data->env;
	if (!exec->cmd[1])
	{
		builtin_env(data, true);
		return (EXIT_SUCCESS);
	}
	if (parsing_export(exec))
		return (EXIT_FAILURE);
	else
	{
		new_var = extract_key_value(exec);
		while (tmp)
		{
			if (ft_strcmp(tmp->key, new_var->key) == 0)
			{
				free(tmp->value);
				tmp->value = new_var->value;
				free(new_var->key);
				free(new_var);
				return (EXIT_SUCCESS);
			}
			tmp = tmp->next;
		}
		tmp = data->env;
		if (data->env)
			ft_lstlast_env(data->env)->next = new_var;
		else
			data->env = new_var;
		new_var->next = NULL;
	}
	return (EXIT_SUCCESS);
}
