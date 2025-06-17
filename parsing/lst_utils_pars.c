
#include "../includes/parsing.h"

int	lstsize_pars(t_pars *pars)
{
	int		i;

	i = 1;
	if (!pars)
		return (0);
	if (!pars->next)
		return (1);
	while (pars->next)
	{
		pars = pars->next;
		i++;
	}
	return (i);
}

void	free_lst_pars(t_pars **pars)
{
	t_pars	*tmp;
	int		size;

	size = lstsize_pars(*pars);
	if (!(*pars))
		return ;
	while (size--)
	{
		tmp = (*pars)->next;
		if ((*pars)->word)
			free((*pars)->word);
		free(*pars);
		*pars = tmp;
	}
	
}

t_pars	*ft_lstlast_pars(t_pars *pars)
{
	if (!pars)
		return (pars);
	while (pars->next)
		pars = pars->next;
	return (pars);
}

int	add_back_pars(t_pars **pars)
{
	t_pars	*node;
	t_pars	*tmp;

	node = ft_calloc(1, sizeof(t_pars));
	if (!node)
		return (1);
	node->next = NULL;
	if (!*pars)
		*pars = node;
	else
	{
		tmp = ft_lstlast_pars(*pars);
		tmp->next = node;
	}
	return (0);
}

void print_lst_pars(t_pars *pars)
{
	while(pars)
	{
		if (pars->type == PIPE)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == PIPE\n", pars->word);
		else if (pars->type == HEREDOC)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == HEREDOC\n", pars->word);
		else if (pars->type == REDIR_APPEND)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == REDIR_APPEND\n", pars->word);
		else if (pars->type == REDIR_TRUNC)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == REDIR_TRUNC\n", pars->word);
		else if (pars->type == REDIR_IN)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == REDIR_IN\n", pars->word);
		else if (pars->type == SIMP_QUOTES)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == SIMP_QUOTES\n", pars->word);
		else if (pars->type == DBL_QUOTES)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == DBL_QUOTES\n", pars->word);
		else if (pars->type == VAR_ENV)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == VAR_ENV\n", pars->word);
		else if (pars->type == COMMANDS)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == COMMANDS\n", pars->word);
		else if (pars->type == ARGS)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == ARGS\n", pars->word);
		else if (pars->type == BUILTINS)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == BUILTINS\n", pars->word);
		else if (pars->type == WORD)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == WORD\n", pars->word);
		else if (pars->type == NAME)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == NAME\n", pars->word);
		else if (pars->type == NUL)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == NUL\n", pars->word);
		else if (pars->type == TARGETS)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == TARGET\n", pars->word);
		else if (pars->type == SYNTERR)
			printf("\033[33mWORD == %s \033[;32m|||||||||| \033[35mTYPE == SYNTERR\n", pars->word);
		pars = pars->next;
	}
}