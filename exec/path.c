/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:44:48 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 02:59:24 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

static char	**find_path_first(t_data *data, t_exec *node);
static int	is_slash(t_exec *exec);
static int	find_path_line(t_data *data);
static char	*search_in_paths(char **allpath, char *cmd);
static char	*try_path(char *dir, char *cmd);

char	*path_in_arg(t_exec *exec)
{
	char	*path;

	if (is_slash(exec) == 1)
	{
		if ((access(exec->cmd[0], F_OK) == -1) || (access(exec->cmd[0], X_OK) ==
				-1))
			return (NULL);
		else
		{
			path = ft_strdup(exec->cmd[0]);
			if (!path)
				return (NULL);
			return (path);
		}
	}
	return (NULL);
}

static int	is_slash(t_exec *exec)
{
	int	j;

	j = 0;
	if (!exec->cmd || !exec->cmd[0])
		return (0);
	while (exec->cmd && exec->cmd[0][j])
	{
		if (exec->cmd[0][j] == '/')
			return (1);
		j++;
	}
	return (0);
}

// char	*find_path(t_exec *node, t_data *data)
// {
// 	char	**allpath;
// 	char	*buff;
// 	char	*path;
// 	int		j;

// 	j = 0;
// 	if (!node->cmd || !node->cmd[0] || ft_strcmp(node->cmd[0], "") == 0)
// 		return (NULL);
// 	allpath = find_path_first(data, node);
// 	while (allpath[++j])
// 	{
// 		buff = ft_strjoin(allpath[j], "/");
// 		if (!buff)
// 			return (NULL);
// 		path = ft_strjoin(buff, node->cmd[0]);
// 		free(buff);
// 		if (!path)
// 			return (NULL);
// 		if (access(path, F_OK && X_OK) == 0)
// 		{
// 			free_tab(allpath);
// 			return (path);
// 		}
// 		free(path);
// 	}
// 	free_tab(allpath);
// 	return (NULL);
// }

char	*find_path(t_exec *node, t_data *data)
{
	char	**allpath;
	char	*path;

	if (!node->cmd || !node->cmd[0] || ft_strcmp(node->cmd[0], "") == 0)
		return (NULL);
	allpath = find_path_first(data, node);
	path = search_in_paths(allpath, node->cmd[0]);
	free_tab(allpath);
	return (path);
}

static char	*search_in_paths(char **allpath, char *cmd)
{
	char	*result;
	int		j;

	j = 0;
	while (allpath[++j])
	{
		result = try_path(allpath[j], cmd);
		if (result)
			return (result);
	}
	return (NULL);
}

static char	*try_path(char *dir, char *cmd)
{
	char	*buff;
	char	*path;

	buff = ft_strjoin(dir, "/");
	if (!buff)
		return (NULL);
	path = ft_strjoin(buff, cmd);
	free(buff);
	if (!path)
		return (NULL);
	if (access(path, F_OK && X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

static char	**find_path_first(t_data *data, t_exec *node)
{
	char	**cmd;
	int		j;

	j = find_path_line(data);
	if (j == -1)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n",
				node->cmd[0]);
		free_all(data, true, 127);
	}
	cmd = ft_split(data->envp[j], ':');
	if (!cmd)
		free_all_msg(data, 0, "split fail path last command\n");
	return (cmd);
}

static int	find_path_line(t_data *data)
{
	int	i;

	i = 1;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	i = 0;
	return (-1);
}
