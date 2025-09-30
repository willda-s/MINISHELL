/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:50:00 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/30 01:00:06 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parsing.h"
#include <stdio.h>
#include <unistd.h>
#include "builtins.h"

static char	*handle_null_path(t_data *data, char *path, char *old_pwd)
{
	path = get_env_value(data->env, "HOME");
	if (path == (void *)1)
	{
		write(2, "cd: HOME not set\n", 17);
		free(old_pwd);
		return (NULL);
	}
	return (path);
}

int	builtin_cd(t_exec *exec, t_data *data)
{
	char	*path;
	char	*old_pwd;

	path = NULL;
	if (ensure_pwd_var(&data->env) < 0)
		return (EXIT_FAILURE);
	old_pwd = getcwd(NULL, 0);
	if (!exec->cmd[1])
	{
		path = handle_null_path(data, path, old_pwd);
		if (!path)
			return (EXIT_FAILURE);
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
