#include "../includes/parsing.h"

char	*get_env_value(t_env *envd, char *key)
{
	while (envd)
	{
		// printf("key = %s\n", key);
		// printf("envd.key = %s\n", envd->key);
		if (ft_strncmp(envd->key, key, ft_strlen(envd->key)) == 0)
		{
			return (envd->value);
		}
		envd = envd->next;
	}
	return ("");
}

int	is_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}