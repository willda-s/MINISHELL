
#include "../includes/parsing.h"

void init_token(t_pars **pars)
{

	t_pars *tmp;

	tmp = *pars;
	while(tmp)
	{
		if (tmp->type == NUL)
		{
			if (access(tmp->word, X_OK) == 0) //je dois rajouter le path pour verifier ca
			{
				tmp->type = COMMANDS;
				if (ft_strncmp(tmp->word, "|", 1) != 0)
					tmp->next->type = ARGUMENT;
			}
			else if (ft_strncmp(tmp->word, "|", 1) == 0)
				tmp->type = PIPE;
			else if (ft_strncmp(tmp->word, "<", 1) == 0 ||ft_strncmp(tmp->word, ">", 1) == 0)
			{
				tmp->type = REDIRECTION;
				if (ft_strncmp(tmp->word, "|", 1) != 0)
					tmp->next->type = REDIRFILES;
			}
		}
		tmp = tmp->next;
	}
}
//X_OK POUR LES COMMANDES ??

//Verifier les nodes type arguments savoir si c'est des options de commandes ou quotes