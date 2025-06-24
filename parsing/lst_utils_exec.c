
#include "../includes/parsing.h"

int	lstsize_exec(t_exec *exec)
{
	int		i;

	i = 1;
	if (!exec)
		return (0);
	if (!exec->next)
		return (1);
	while (exec->next)
	{
		exec = exec->next;
		i++;
	}
	return (i);
}

// void	free_lst_exec(t_exec **exec)
// {
// 	t_exec	*tmp;
// 	int		size;

// 	size = lstsize_exec(*exec);
// 	if (!(*exec))
// 		return ;
// 	while (size--)
// 	{
// 		tmp = (*exec)->next;
// 		if ((*exec)->word)
// 			free((*exec)->word);
// 		free(*exec);
// 		*exec = tmp;
// 	}
	
// }

t_exec	*ft_lstlast_exec(t_exec *exec)
{
	if (!exec)
		return (exec);
	while (exec->next)
		exec = exec->next;
	return (exec);
}

int	add_back_exec(t_exec **exec)
{
	t_exec	*node;
	t_exec	*tmp;

	node = ft_calloc(1, sizeof(t_exec));
	if (!node)
		return (1);
	node->next = NULL;
	if (!*exec)
		*exec = node;
	else
	{
		tmp = ft_lstlast_exec(*exec);
		tmp->next = node;
	}
	return (0);
}
// void print_lst_redir(t_redir *redir)
// {
// 	while(redir)
// 	{
// 		printf("token = %u\n", redir->token);
// 		printf("file_in = %s\n", redir->filename);
// 		printf("file_out = %s\n", redir->delimiter);
// 		redir = redir->next;
// 	}
// }

void print_lst_exec(t_exec *exec)
{
	int j = 0;
	int i;
	t_redir *tmp;
	while(exec)
	{
		i = 0;
		printf("-------------noeud [%d]---------------------\n", j++);
		while (exec->cmd && exec->cmd[i])
		{
			printf("cmd[%d] = %s\n", i, exec->cmd[i]);
			i++;
		}
		tmp = exec->redir;
		while(tmp)
		{
			printf("token = %u\n", tmp->token);
			printf("file = %s\n", tmp->filename);
			printf("delimiter = %s\n", tmp->delimiter);
			tmp = tmp->next;
		}
		exec = exec->next;
	}
}

size_t count_cmd(t_pars *pars)
{
	size_t i = 0;
	if (pars->type == COMMANDS)
	{
		i++;
		pars = pars->next;
		while (pars && pars->type != PIPE)
		{
			if (pars->type == ARGS)
				i++;
			pars = pars->next;
		}
	}
	return (i);
}

char **init_cmds(t_pars *pars, t_exec **node)
{
	t_pars *tmp;
	size_t ccmd;
	int i = 1;

	ccmd = count_cmd(pars);
	if (pars->type == COMMANDS || pars->type == BUILTINS)
	{
		ccmd = count_cmd(pars);
		(*node)->cmd = malloc(sizeof(char *) * (ccmd + 1));
		if (!(*node)->cmd)
			return (NULL) ; //secure
		(*node)->cmd[0] = ft_strdup(pars->word);
		if (!(*node)->cmd || !(*node)->cmd[0])
			return (NULL)  ; //secure
		tmp = pars->next;
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type == ARGS)
			{
				(*node)->cmd[i] = ft_strdup(tmp->word);
				if (!(*node)->cmd[i])
					return (NULL) ;
				i++;
			}
				tmp = tmp->next;
		}
		(*node)->cmd[i] = NULL;
	}
	else
		(*node)->cmd = NULL;
	return ((*node)->cmd);
}

void init_filename_and_token(t_redir **node, t_pars *tmp)
{
	if (tmp && tmp->type & REDIR)
	{
		if (tmp->type == REDIR_IN && tmp->next)
		{
			(*node)->filename = ft_strdup(tmp->next->word);
			(*node)->token = REDIR_IN;
		}
		else if (tmp->type == HEREDOC && tmp->next && (*node)->token != HEREDOC)
		{
			(*node)->delimiter = ft_strdup(tmp->next->word);
			(*node)->token = HEREDOC;
		}
		else if (tmp->type == REDIR_APPEND && tmp->next)
		{
			(*node)->filename = ft_strdup(tmp->next->word);
			(*node)->token = REDIR_APPEND;
		}
		else if (tmp->type == REDIR_TRUNC && tmp->next)
		{
			(*node)->filename = ft_strdup(tmp->next->word);
			(*node)->token = REDIR_TRUNC;
		}
	}
}
void init_lst_redir(t_exec **exec, t_pars *pars)
{
	t_redir *node;

	node = NULL;
	if (pars && pars->type & REDIR)
	{
		if (add_back_redir(&(*exec)->redir) == 1)
			return ;
		node = ft_lstlast_redir((*exec)->redir);
		if (!node)
			return ;
		init_filename_and_token(&node, pars);
	}
}
void init_lst_exec(t_exec **exec, t_pars *pars) 
{
	t_exec *node;
	int i;

	i = 1;
	node = NULL;
	while(pars)
	{
		if (add_back_exec(exec) == 1)
			return ;
		node = ft_lstlast_exec(*exec);
		if (!node)
			return ;
		while (pars && pars->type != PIPE)
		{
			if (!node->cmd)
				node->cmd = init_cmds(pars, &node);
			init_lst_redir(&node, pars);
			pars = pars->next;
		}
		if (pars && pars->type == PIPE)
			pars = pars->next;
	}
}



//1.Creer le node dans tout les cas
//2. Verifier un REDIRIN avant la commande
//2. Si y'a un type commande, alors remplir le char ** en cherchant ses arguments avant le pipe
//3. Verifier un REDIROUT avant de passer au noeud d'apres

// < in.txt < in.txt < in.txt : rien ne se passe
// > out.txt > out.txt > out.txt : same
// << in : heredoc creer et c tout
// >> out : rien

//sans commande les redirec ne font rien a par heredoc creer et prioriser dasn tout les cas 
