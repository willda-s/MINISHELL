/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:50:00 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/27 19:28:27 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parsing.h"
#include "builtins.h"
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

static bool wrapper_chdir(char *path, char *old_pwd)
{
	if (chdir(path) == -1)
	{
		write(2, "cd: ", 4);
		perror(path);
		free(old_pwd);
		return (false);
	}
	return (true);
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
	if (!wrapper_chdir(path, old_pwd))
		return (EXIT_FAILURE);
	update_pwd_vars(data->env, old_pwd);
	free(old_pwd);
	return (EXIT_SUCCESS);
}
