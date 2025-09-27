/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:25:08 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/27 19:28:40 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <unistd.h>
#include "libft.h"

int	set_node(t_env *node, const char *key, const char *value)
{	
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
	return (0);
}
int	add_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*node;
	t_env	*tmp;

	node = NULL;
	if (set_node(node, key, value) == -1)
		return (-1);
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

int handle_no_pwd(int has_pwd, int error_control, t_env **env)
{
	char *cwd;

	if (!has_pwd)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (-1);
		error_control = add_env_var(env, "PWD", cwd);
		free(cwd);
	}
	return (0);
}

int	ensure_pwd_var(t_env **env)
{
	int		has_pwd;
	int		has_oldpwd;
	int		error_control;
	t_env	*tmp;

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
	if (handle_no_pwd(has_pwd, error_control, env) == -1)
		return (-1);
	if (!has_oldpwd)
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