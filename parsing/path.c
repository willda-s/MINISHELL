/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:44:48 by willda-s          #+#    #+#             */
/*   Updated: 2025/05/16 21:20:01 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

// void	find_path_line(t_data *data)
// {
// 	int	i;

// 	i = 1;
// 	while (data->env[i])
// 	{
// 		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
// 		{
// 			data->i = i;
// 			return ;
// 		}
// 		i++;
// 	}
// 	data->i = 0;
// 	return ;
// }

// int	is_slash(t_data *data, int i)
// {
// 	int	j;

// 	j = 0;
// 	while (data->av[i][j])
// 	{
// 		if (data->av[i][j] == '/')
// 			return (1);
// 		j++;
// 	}
// 	return (0);
// }

// char	*path_in_arg(t_data *data, int i, int file)
// {
// 	char	*path;

// 	if (is_slash(data, i) == 1)
// 	{
// 		if ((access(data->cmd[0], F_OK) == -1)
// 			|| (access(data->cmd[0], X_OK) == -1))
// 			return (NULL);
// 		else
// 		{
// 			path = ft_strdup(data->cmd[0]);
// 			if (!path)
// 				return (free_and_exit(data, file, "strdup error\n"), NULL);
// 			return (path);
// 		}
// 	}
// 	return (NULL);
// }

// static char	**find_path_first(t_data *data, bool file)
// {
// 	char	**cmd;

// 	find_path_line(data);
// 	if (data->i == 0)
// 		free_and_exit(data, file, "no path=\n");
// 	cmd = ft_split(data->env[data->i], ':');
// 	if (!cmd)
// 		free_and_exit(data, file, "split fail path last command\n");
// 	return (cmd);
// }

// char	*find_path(t_data *data, bool file)
// {
// 	char	**allpath;
// 	char	*buff;
// 	char	*path;
// 	int		j;

// 	j = 0;
// 	allpath = find_path_first(data, file);
// 	while (allpath[++j])
// 	{
// 		buff = ft_strjoin(allpath[j], "/");
// 		if (!buff)
// 			return (free_strs(allpath), NULL);
// 		path = ft_strjoin(buff, data->cmd[0]);
// 		free(buff);
// 		if (!path)
// 			return (free_strs(allpath), NULL);
// 		if (access(path, F_OK && X_OK) == 0)
// 			return (free_strs(allpath), path);
// 		free(path);
// 	}
// 	free_strs(allpath);
// 	return (NULL);
// }
