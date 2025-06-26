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

static int count_env(t_data *data)
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
	t_env *tmp;
	int i;

	i = count_env(data);
    data->envp = malloc(sizeof(char *) * (i + 1));
    if (!data->envp)
        return ;
    i = 0;
    tmp = data->env;
    while (tmp)
    {
        data->envp[i] = ft_strjoin(tmp->key, "=");
        if (!data->envp[i])
            return ;
        data->envp[i] = ft_strjoin(data->envp[i], tmp->value);
        if (!data->envp[i])
            return ;
        i++;
        tmp = tmp->next;
    }
    data->envp[i] = NULL;
}
