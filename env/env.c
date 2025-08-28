/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:53:49 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/28 14:09:20 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	init_lst_env(t_env **envd, char **env)
{
	t_env	*node;
	int		i;

	i = 0;
	while (env && env[i])
	{
		if (add_back_env(envd) == 1)
			exit(EXIT_FAILURE);
		node = ft_lstlast_env(*envd);
		if (!node)
			free_lst_env(envd, true, 0);
		node->key = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i]);
		if (!node->key)
			free_lst_env(envd, true, 0);
		node->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!node->value)
			free_lst_env(envd, true, 0);
		i++;
	}
}

static int	count_env(t_data *data)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = data->env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	init_envp(t_data *data)
{
	t_env	*tmp;
	char	*str;
	int		i;

	i = count_env(data);
	data->envp = ft_calloc((i + 1), sizeof(char *));
	if (!data->envp)
		free_all(data, 0, "Error\nMalloc fail in init_envp\n", true);
	i = 0;
	tmp = data->env;
	while (tmp)
	{
		str = ft_strjoin(tmp->key, "=");
		if (!str)
			free_all(data, 0, "Error\nMalloc fail in init_envp\n", true);
		data->envp[i] = ft_strjoin(str, tmp->value);
		free(str);
		if (!data->envp || !data->envp[i])
			free_all(data, 0, "Error\nMalloc fail in init_envp\n", true);
		i++;
		tmp = tmp->next;
	}
	data->envp[i] = NULL;
}
