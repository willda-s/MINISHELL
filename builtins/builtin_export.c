/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:08 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/28 22:45:31 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "parsing.h"
#include <stddef.h>
#include <stdio.h>

static int	parsing_export(t_exec *exec, size_t index)
{
	int	i;

	i = 0;
	while (exec->cmd && exec->cmd[index][i] && exec->cmd[index][i] != '=')
	{
		if (!ft_isalnum(exec->cmd[index][i]) && exec->cmd[index][i] != '_')
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

static t_env	*extract_key_value(t_exec *exec, size_t index)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = extract_key(exec->cmd[index]);
	if (ft_strchr(exec->cmd[index], '='))
		env->value = extract_value(exec->cmd[index]);
	else
		env->value = NULL;
	env->next = NULL;
	return (env);
}

static void	export_free(t_env *new_var, t_env *tmp)
{
	if (new_var->value)
	{
		free(tmp->value);
		tmp->value = new_var->value;
	}
	free(new_var->key);
	free(new_var);
}

int	builtin_export(t_exec *exec, t_data *data)
{
	t_env	*new_var;
	t_env	*tmp;
	size_t	i;

	tmp = data->env;
	if (!exec->cmd[1])
	{
		builtin_env(data, true);
		return (EXIT_SUCCESS);
	}
	i = 1;
	while (exec->cmd[i])
	{
		tmp = data->env;
		if (parsing_export(exec, i))
			return (EXIT_FAILURE);
		else
		{
			new_var = extract_key_value(exec, i);
			while (tmp)
			{
				if (ft_strcmp(tmp->key, new_var->key) == 0)
				{
					export_free(new_var, tmp);
					break ;
				}
				tmp = tmp->next;
			}
			if (!tmp)
			{
				if (data->env)
					ft_lstlast_env(data->env)->next = new_var;
				else
					data->env = new_var;
				new_var->next = NULL;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
