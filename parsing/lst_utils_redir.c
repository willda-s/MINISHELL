#include "../includes/parsing.h"

int	lstsize_redir(t_redir *redir)
{
	int		i;

	i = 1;
	if (!redir)
		return (0);
	if (!redir->next)
		return (1);
	while (redir->next)
	{
		redir = redir->next;
		i++;
	}
	return (i);
}

void	free_lst_redir(t_redir **redir)
{
	t_redir	*tmp;
	int		size;

	size = lstsize_redir(*redir);
	if (!(*redir))
		return ;
	while (size--)
	{
		tmp = (*redir)->next;
		if ((*redir)->filename)
			free((*redir)->filename);
		if ((*redir)->delimiter)
			free((*redir)->delimiter);
		free(*redir);
		*redir = tmp;
	}
	
}

t_redir	*ft_lstlast_redir(t_redir *redir)
{
	if (!redir)
		return (redir);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

int	add_back_redir(t_redir **redir)
{
	t_redir	*node;
	t_redir	*tmp;

	node = ft_calloc(1, sizeof(t_redir));
	if (!node)
		return (1);
	node->next = NULL;
	if (!*redir)
		*redir = node;
	else
	{
		tmp = ft_lstlast_redir(*redir);
		tmp->next = node;
	}
	return (0);
}