/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:49:41 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/25 23:55:30 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
//#include "builtins.h"
#include "libft.h"

static void	add_last_env_var(t_env **env, t_env *node)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

static int	add_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*node;

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
		add_last_env_var(env, node);
	return (0);
}

static int	search_pwd(t_env *tmp)
{
	int	has_pwd;

	has_pwd = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
			has_pwd = 1;
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			has_pwd = 2;
		tmp = tmp->next;
	}
	return (has_pwd);
}

int	ensure_pwd_var(t_env **env)
{
	int		has_pwd;
	int		error_control;
	t_env	*tmp;
	char	*cwd;

	error_control = 0;
	tmp = *env;

	has_pwd = search_pwd(tmp);
	if (has_pwd != 1)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (-1);
		error_control = add_env_var(env, "PWD", cwd);
		free(cwd);
	}
	if (has_pwd != 2)
		error_control = add_env_var(env, "OLDPWD", "");
	if (error_control < 0)
		return (-1);
	return (0);
}

void	update_pwd_vars(t_env *env, char *old_pwd)
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
