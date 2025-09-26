/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:50:00 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/26 03:39:59 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// static char	*get_env_value(t_env *env, char *key)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->key, key) == 0)
// 			return (tmp->value);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

static int	add_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*node;
	t_env	*tmp;

	node = malloc(sizeof(t_env));
	if (!node)
		return (-1);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (-1);
	}
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node);
		free(node->key);
		return (-1);
	}
	node->next = NULL;
	if (!*env)
		*env = node;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (0);
}

static int	ensure_pwd_var(t_env **env)
{
	int		has_pwd;
	int		has_oldpwd;
	int		error_control;
	t_env	*tmp;
	char	*cwd;

	has_pwd = 0;
	has_oldpwd = 0;
	error_control = 0;
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
			has_pwd = 1;
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			has_oldpwd = 1;
		tmp = tmp->next;
	}
	if (!has_pwd)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (-1);
		error_control = add_env_var(env, "PWD", cwd);
		free(cwd);
	}
	if (!has_oldpwd)
		error_control = add_env_var(env, "OLDPWD", "");
	if (error_control < 0)
		return (-1);
	return (0);
}

static void	update_pwd_vars(t_env *env, char *old_pwd)
{
	char	*new_pwd;
	t_env	*tmp;

	new_pwd = getcwd(NULL, 0);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = new_pwd;
		}
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(old_pwd);
		}
		tmp = tmp->next;
	}
}

int	builtin_cd(t_exec *exec, t_data *data)
{
	char	*path;
	char	*old_pwd;

	if (ensure_pwd_var(&data->env) < 0)
		return (EXIT_FAILURE);
	old_pwd = getcwd(NULL, 0);
	if (!exec->cmd[1])
	{
		path = get_env_value(data->env, "HOME");
		if (path == (void *)1)
		{
			write(2, "cd: HOME not set\n", 17);
			free(old_pwd);
			return (EXIT_FAILURE);
		}
	}
	else
		path = exec->cmd[1];
	if (chdir(path) == -1)
	{
		write(2, "cd: ", 4);
		perror(path);
		free(old_pwd);
		return (EXIT_FAILURE);
	}
	update_pwd_vars(data->env, old_pwd);
	free(old_pwd);
	return (EXIT_SUCCESS);
}
