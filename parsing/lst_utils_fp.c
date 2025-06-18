
#include "../includes/parsing.h"

int	lstsize_fp(t_finalpars *fp)
{
	int		i;

	i = 1;
	if (!fp)
		return (0);
	if (!fp->next)
		return (1);
	while (fp->next)
	{
		fp = fp->next;
		i++;
	}
	return (i);
}

// void	free_lst_pars(t_finalpars **fd)
// {
// 	t_finalpars	*tmp;
// 	int		size;

// 	size = lstsize_pars(*fd);
// 	if (!(*fd))
// 		return ;
// 	while (size--)
// 	{
// 		tmp = (*fd)->next;
// 		if ((*fd)->word)
// 			free((*fd)->word);
// 		free(*fd);
// 		*fd = tmp;
// 	}
	
// }

t_finalpars	*ft_lstlast_fp(t_finalpars *fp)
{
	if (!fp)
		return (fp);
	while (fp->next)
		fp = fp->next;
	return (fp);
}

int	add_back_fp(t_finalpars **fp)
{
	t_finalpars	*node;
	t_finalpars	*tmp;

	node = ft_calloc(1, sizeof(t_finalpars));
	if (!node)
		return (1);
	node->next = NULL;
	if (!*fp)
		*fp = node;
	else
	{
		tmp = ft_lstlast_fp(*fp);
		tmp->next = node;
	}
	return (0);
}

void print_lst_fp(t_finalpars *fp)
{
	int i = 0;
	while(fp)
	{
		printf("unit = %s\n", fp->unit);
		printf("fdin_filename = %s\n", fp->fdin_filename);
		printf("fdout_filename = %s\n", fp->fdout_filename);
		while (fp->arg && fp->arg[i++])
			printf("arg[%d] = %s\n", i, fp->arg[i]);
		fp = fp->next;
	}
}

void init_lst_fp(t_finalpars **fp, t_pars *pars)
{
	t_finalpars *node;
	int i;

	i = 0;
	while(pars)
	{
		if (pars->type == COMMANDS)
		{
			if (add_back_fp(fp) == 1)
				return ;
			node = ft_lstlast_fp(*fp);
			if (!node)
				return ;
			node->unit = ft_strdup(pars->word);
			if (!node->unit)
				return ;
			// node->arg = NULL;
			// node->fdin = 0;
			// node->fdout = 0;
			// pars = pars->next;
			// while (pars->type != PIPE)
			// {
			// 	if (pars->type == ARGS)
			// 	{
			// 		node->arg[i] = ft_strdup(pars->word);
			// 		if (!node->arg[i])
			// 			return;
			// 		i++;
			// 	}
				// pars = pars->next;
		}
		else
		{
			
			if (node && pars->type == REDIRIN)
			{
				node->fdin_filename = ft_strdup(pars->next->word);
				if (!node->fdin_filename)
					return;
			}
			else if (node && pars->type == REDIROUT)
			{
				node->fdout_filename = ft_strdup(pars->next->word);
				if (!node->fdout_filename)
					return;
			}
		}
		pars = pars->next;
	}
}