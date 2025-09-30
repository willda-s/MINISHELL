/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:44:48 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 20:32:22 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

static char	**find_path_first(t_data *data, t_exec *node);
static int	find_path_line(t_data *data);
static char	*search_in_paths(char **allpath, char *cmd);
static char	*try_path(char *dir, char *cmd);

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
