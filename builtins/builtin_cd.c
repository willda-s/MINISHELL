/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:50:00 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/11 20:36:49 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

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

	old_pwd = getcwd(NULL, 0);
	if (!exec->cmd[1])
		path = get_env_value(data->env, "HOME");
	else
		path = exec->cmd[1];
	if (!path)
	{
		write(2, "cd: HOME not set\n", 17);
		free(old_pwd);
		return (EXIT_FAILURE);
	}
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
