
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

void	free_lst_exec(t_exec **exec)
{
	t_exec	*tmp;
	int		size;

	size = lstsize_exec(*exec);
	if (!(*exec))
		return ;
	while (size--)
	{
		tmp = (*exec)->next;
		if ((*exec)->cmd)
			free_tab((*exec)->cmd);
		if ((*exec)->path)
			free((*exec)->path);
		if ((*exec)->redir)
			free_lst_redir(&(*exec)->redir);
		free(*exec);
		*exec = tmp;
	}
	
}

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

// char **init_cmds(t_pars *pars, t_exec **node)
// {
// 	t_pars *tmp;
// 	size_t ccmd;
// 	int i;
	
// 	i = 1;
// 	if (pars->type == COMMANDS || pars->type == BUILTINS)
// 	{
// 		ccmd = count_cmd(pars);
// 		(*node)->cmd = malloc(sizeof(char *) * (ccmd + 1));
// 		if (!(*node)->cmd)
// 			return (NULL) ; //secure
// 		(*node)->cmd[0] = ft_strdup(pars->word);
// 		if (!(*node)->cmd || !(*node)->cmd[0])
// 			return (NULL)  ; //secure
// 		tmp = pars->next;
// 		while (tmp && tmp->type != PIPE)
// 		{
// 			if (tmp->type == ARGS)
// 			{
// 				(*node)->cmd[i] = ft_strdup(tmp->word);
// 				if (!(*node)->cmd[i])
// 					return (NULL) ; //secure
// 				i++;
// 			}
// 				tmp = tmp->next;
// 		}
// 		(*node)->cmd[i] = NULL;
// 	}
// 	else
// 		(*node)->cmd = NULL;
// 	return ((*node)->cmd);
// }

static int fill_args(t_pars *pars, t_exec *node)
{
    int i = 1;

    while (pars && pars->type != PIPE)
    {
        if (pars->type == ARGS)
        {
            node->cmd[i] = ft_strdup(pars->word);
            if (!node->cmd[i])
                return (1);
            i++;
        }
        pars = pars->next;
    }
    node->cmd[i] = NULL;
    return (0);
}

char **init_cmds(t_data *data, t_pars *tmp, t_exec **node)
{
    size_t ccmd;
    if (tmp->type == COMMANDS || tmp->type == BUILTINS)
    {
        ccmd = count_cmd(tmp);
        (*node)->cmd = malloc(sizeof(char *) * (ccmd + 1));
        if (!(*node)->cmd)
            free_all(data, 0, "Error\nMalloc fail in init_cmds\n");
        (*node)->cmd[0] = ft_strdup(tmp->word);
        if (!(*node)->cmd[0])
            free_all(data, 0, "Error\nMalloc fail in init_cmds\n");
        if (fill_args(tmp->next, *node) == 1)
            free_all(data, 0, "Error\nMalloc fail in fill_args\n");
    }
    else
        (*node)->cmd = NULL;
    return ((*node)->cmd);
}

static void check_redirin(t_data *data, t_pars *tmp, t_redir **node)
{
	if (tmp->type == REDIR_IN && tmp->next)
	{
		(*node)->filename = ft_strdup(tmp->next->word);
		if (!(*node)->filename)
			free_all(data, 0, "Error\nMalloc fail in check_redirin\n");
		(*node)->token = REDIR_IN;
	}
	else if (tmp->type == HEREDOC && tmp->next && (*node)->token != HEREDOC)
	{
		(*node)->delimiter = ft_strdup(tmp->next->word); //rajouter le \n pour le heredoc
		if (!(*node)->delimiter)
			free_all(data, 0, "Error\nMalloc fail in check_redirin\n");
		(*node)->token = HEREDOC;
	}
}

static void check_redirout(t_data *data, t_pars *tmp, t_redir **node)
{
	if (tmp->type == REDIR_APPEND && tmp->next)
	{
		(*node)->filename = ft_strdup(tmp->next->word);
		if (!(*node)->filename)
			free_all(data, 0, "Error\nMalloc fail in check_redirout\n");
		(*node)->token = REDIR_APPEND;
	}
	else if (tmp->type == REDIR_TRUNC && tmp->next)
	{
		(*node)->filename = ft_strdup(tmp->next->word);
		if (!(*node)->filename)
			free_all(data, 0, "Error\nMalloc fail in check_redirout\n");		
		(*node)->token = REDIR_TRUNC;
	}
}
void init_filename_and_token(t_redir **node, t_pars *tmp, t_data *data)
{
	if (tmp && tmp->type & REDIR)
	{
		check_redirin(data, tmp, node);
		check_redirout(data, tmp, node);
	}
}
void init_lst_redir(t_exec **exec, t_pars *pars, t_data *data)
{
	t_redir *node;

	node = NULL;
	if (pars && pars->type & REDIR)
	{
		if (add_back_redir(&(*exec)->redir) == 1)
			free_all(data, 0, "Error\nAdd_back fail in init_lst_redir\n");
		node = ft_lstlast_redir((*exec)->redir);
		if (!node)
			free_all(data, 0, "Error\nFt_lstlast_redir fail\n");
		init_filename_and_token(&node, pars, data);
	}
}
// int init_lst_exec(t_exec **exec, t_pars *pars) 
// {
// 	t_exec *node;

// 	node = NULL;
// 	while(pars)
// 	{
// 		if (add_back_exec(exec) == 1)
// 			return (1);
// 		node = ft_lstlast_exec(*exec);
// 		if (!node)
// 			return (1);
// 		while (pars && pars->type != PIPE)
// 		{
// 			if (!node->cmd)
// 				node->cmd = init_cmds(pars, &node);
// 			init_lst_redir(&node, pars);
// 			pars = pars->next;
// 		}
// 		if (pars && pars->type == PIPE)
// 			pars = pars->next;
// 	}
// 	return (0);
// }


void init_lst_exec(t_data *data) 
{
	t_exec *node;
	t_pars *tmp;

	node = NULL;
	tmp = data->pars;
	while(tmp)
	{
		if (add_back_exec(&(data)->exec) == 1)
			free_all(data, 0, "Error\nAdd_back fail in init_lst_exec\n");
		node = ft_lstlast_exec(data->exec);
		if (!node)
			free_all(data, 0, "Error\nFt_lstlast fail\n");
		while (tmp && tmp->type != PIPE)
		{
			if (!node->cmd)
				node->cmd = init_cmds(data, tmp, &node);
			init_lst_redir(&node, tmp, data);
			tmp = tmp->next;
		}
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
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
