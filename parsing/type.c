
#include "../includes/parsing.h"

bool is_redirection(t_pars **tmp)
{
	if (ft_strncmp((*tmp)->word, ">", ft_strlen((*tmp)->word)) == 0)
		(*tmp)->type = REDIR_TRUNC;
	else if (ft_strncmp((*tmp)->word, "<", ft_strlen((*tmp)->word)) == 0)
		(*tmp)->type = REDIR_IN;
	else if (ft_strncmp((*tmp)->word, "<<", ft_strlen((*tmp)->word)) == 0)
		(*tmp)->type = HEREDOC;
	else if (ft_strncmp((*tmp)->word, ">>", ft_strlen((*tmp)->word)) == 0)
		(*tmp)->type = REDIR_APPEND;
	if ((*tmp)->type != NUL)
		return (true);
	else
		return (false);
}

void init_token_command(t_pars **pars)
{
	t_pars *tmp;

	tmp = *pars;
	while(tmp)
	{
		if (tmp->type == NUL)
		{
			tmp->type = COMMANDS;
			while (tmp->next && tmp->next->type != PIPE)
			{
				tmp = tmp->next;
				if (tmp->type == NUL)
					tmp->type = ARGS;
			}
		}
		tmp = tmp->next;
	}
}

void init_token_redir(t_pars **pars)
{
	t_pars *tmp;

	tmp = *pars;
	while(tmp)
	{
		if (tmp->type == NUL)
		{
			if (is_redirection(&tmp))
			{
				if (tmp->next)
					tmp->next->type = TARGETS;
			}
		}
		tmp = tmp->next;
	}
}
void init_token(t_pars **pars)
{
	t_pars *tmp;

	tmp = *pars;
	while(tmp)
	{
		if (ft_strncmp(tmp->word, "|", ft_strlen(tmp->word)) == 0)
			tmp->type = PIPE;
		tmp = tmp->next;
	}
}

void token_main(t_pars **pars)
{
	init_token_redir(pars);
	init_token(pars);
	init_token_command(pars);

}

//Autre chose a interpreter ?

//prio des token ???? : 1. redirection 2. Pipe 3. commands et args ?


