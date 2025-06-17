
#include "../includes/parsing.h"

bool	is_not_interpretable(char *str)
{
	int i;

	i = 0;
	while(NOTINTERPRET[i])
	{
		if (ft_strncmp(str, &NOTINTERPRET[i], ft_strlen(str)) == 0)
			return (true);
		i++;
	}
	return (false);
}

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
			while (tmp->next && tmp->next->type != PIPE /*&& tmp->next->type != SYNTERR*/) //est un type ARGS jusqu'a un type PIPE (ou type SYNTERR)
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
		if (tmp->type == NUL)
		{
			if (ft_strncmp(tmp->word, "|", ft_strlen(tmp->word)) == 0)
				tmp->type = PIPE;
			else if (is_not_interpretable(tmp->word))
				tmp->type = SYNTERR;
			// else if (ft_strncmp(tmp->word, "\"", 1) == 0)
			// 	tmp->type = DBL_QUOTES;
			// else if (ft_strncmp(tmp->word, "'", 1) == 0)
			// 	tmp->type = SIMP_QUOTES;
			// else if (!is_identifier(tmp->word))
			// 	tmp->type = WORD;
		}
		tmp = tmp->next;
	}
}

// void init_token_varenv(t_pars **pars)
// {
// 	t_pars *tmp;

// 	tmp = *pars;
// 	while(tmp)
// 	{
// 		if (tmp->type == word)
// 	}
// }

void token_main(t_pars **pars)
{
	init_token_redir(pars);
	init_token(pars);
	init_token_command(pars);
}

//Comment interpreter les parentheses ?

//Autre chose a interpreter ?

//prio des token ???? : 1. redirection 2. Pipe 3. commands et args ?