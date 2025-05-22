
#include "../includes/parsing.h"

bool	is_metachars(char *str)
{
	int i;

	i = 0;
	while(METACHARS[i])
	{
		if (ft_strncmp(str, &METACHARS[i], ft_strlen(str)) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool is_identifier(char *str)
{
	int i;

	i = 0;
	if (str[0] == '_')
		return (true);
	if (ft_isdigit(str[0]))
		return (false);
	while((str && str[i]) && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		if (str[i + 1] == '\0')
			return (true);
		i++;
	}
	return(false);
}
void init_token(t_pars **pars)
{

	t_pars *tmp;

	tmp = *pars;
	while(tmp)
	{
		if (tmp->type == NUL)
		{
			if (is_metachars(tmp->word))
				tmp->type = METACHAR;
			else if (is_identifier(tmp->word))
				tmp->type = NAME;
			else
				tmp->type = WORD;
		}
		tmp = tmp->next;
	}
}
//X_OK POUR LES COMMANDES ?? <-- a l'exec

//Comment interpreter les parentheses ?

//Autre chose a interpreter ?