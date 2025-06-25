
#include "../includes/parsing.h"

void init_lst_env(t_env **envd, char **env)
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
			return ;
		node->key = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i]);
		if (!node->key)
			free_lst_env(envd);
		node->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!node->value)
			free_lst_env(envd);
		i++;
	}
}

void init_envp(t_data *data)
{
	int i;

	i = 0;
	data->envp = malloc(100);
	while(data->env)
	{
		data->envp[i] = ft_strjoin(data->env->key, "=");
		// if (!data->envp[i])
		data->envp[i] = ft_strjoin(data->envp[i], data->env->value);
		// if (!data->envp[i])
		i++;
	}
}
