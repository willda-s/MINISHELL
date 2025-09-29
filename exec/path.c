/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:44:48 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 01:02:01 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"

static char	**find_path_first(t_data *data, t_exec *node);

static char	*wrapper_access(char *path, char **allpath)
{
	if (access(path, F_OK && X_OK) == 0)
	{
		free_tab(allpath);
		return (path);
	}
	return (NULL);
}

char	*find_path(t_exec *node, t_data *data)
{
	char	**allpath;
	char	*buff;
	char	*path;
	int		j;

	j = 0;
	if (!node->cmd || !node->cmd[0] || ft_strcmp(node->cmd[0], "") == 0)
		return (NULL);
	allpath = find_path_first(data, node);
	while (allpath[++j])
	{
		buff = ft_strjoin(allpath[j], "/");
		if (!buff)
			return (NULL);
		path = ft_strjoin(buff, node->cmd[0]);
		free(buff);
		if (!path)
			return (NULL);
		free(path);
	}
	path = wrapper_access(path, allpath);
	free_tab(allpath);
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
