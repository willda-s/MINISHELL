/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:08 by cafabre           #+#    #+#             */
/*   Updated: 2025/10/01 00:20:57 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "parsing.h"

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

static void	handle_export_var(t_env *existing, t_env *new_var, t_data *data)
{
	if (existing)
	{
		export_free(new_var, existing);
		return ;
	}
	if (data->env)
		ft_lstlast_env(data->env)->next = new_var;
	else
		data->env = new_var;
	new_var->next = NULL;
}

static t_env	*find_env_var(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	builtin_export(t_exec *exec, t_data *data)
{
	t_env	*new_var;
	t_env	*existing;
	size_t	i;

	if (!exec->cmd[1])
	{
		builtin_env(data, true);
		return (EXIT_SUCCESS);
	}
	i = 0;
	while (exec->cmd[++i])
	{
		if (parsing_export(exec, i))
			return (EXIT_FAILURE);
		new_var = extract_key_value(exec, i, data);
		if (!new_var)
			return (2);
		existing = find_env_var(data->env, new_var->key);
		handle_export_var(existing, new_var, data);
	}
	return (EXIT_SUCCESS);
}
