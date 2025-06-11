#include "../includes/parsing.h"

char	*get_env_value(t_env *envd, char *key) //recupere la bonne variable d'environnement
{
	while (envd)
	{
		if (ft_strncmp(envd->key, key, ft_strlen(key)) == 0)
			return (envd->value);
		envd = envd->next;
	}
	return ("");
}

int	is_var_start(char c) //verifie si le caractere est un debut de variable d'environnement
{
	return (ft_isalpha(c) || c == '_');
}

int	is_var_char(char c) //verifie si le caractere est un caractere valide pour une variable d'environnement
{
	return (ft_isalnum(c) || c == '_');
}