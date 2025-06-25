
#include "../includes/env.h"

int	lstsize_env(t_env *envd)
{
	int		i;

	i = 1;
	if (!envd)
		return (0);
	if (!envd->next)
		return (1);
	while (envd->next)
	{
		envd = envd->next;
		i++;
	}
	return (i);
}

int	free_lst_env(t_env **envd)
{
	t_env	*tmp;
	int		size;

	size = lstsize_env(*envd);
	if (!(*envd))
		return (1);
	while (size--)
	{
		tmp = (*envd)->next;
		if ((*envd)->key) //Necessaire ??
			free((*envd)->key);
		if ((*envd)->value) // //
			free((*envd)->value);
		free(*envd);
		*envd = tmp;
	}
	exit(0);
}

t_env	*ft_lstlast_env(t_env *envd)
{
	if (!envd)
		return (envd);
	while (envd->next)
		envd = envd->next;
	return (envd);
}

int	add_back_env(t_env **envd)
{
	t_env	*node;
	t_env	*tmp;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (1);
	node->next = NULL;
	if (!*envd)
		*envd = node;
	else
	{
		tmp = ft_lstlast_env(*envd);
		tmp->next = node;
	}
	return (0);
}

void print_lst_env(t_env *envd)
{
	while(envd)
	{
		printf("%s=%s\n", envd->key, envd->value);
		envd = envd->next;
	}
}