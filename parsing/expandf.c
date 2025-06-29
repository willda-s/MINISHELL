#include "../includes/parsing.h"

static int	ft_expand_var(char *res, int j, char *word, t_data *data) //refacto
{
    char	var[256];
    char	*val;
    int		k;

    data->i++;
    k = 0;
    if (!word[data->i] || (!is_var_char(word[data->i]) && word[data->i] != '"' && word[data->i] != '\''))
    {
        res[j++] = '$';
        return (j);
    }
    while (word[data->i] && is_var_char(word[data->i]) && word[data->i] != '"' && word[data->i] != '\'' && k < 255)
        var[k++] = word[(data->i)++];
    var[k] = '\0';
    val = get_env_value(data->env, var);
    k = 0;
    while (val && val[k])
        res[j++] = val[k++];
    return (j);
}

static int	ft_handle_squotes(char *res, int j, char *word, t_data *data)
{
    data->i++;
    while (word[data->i] && word[data->i] != '\'')
        res[j++] = word[data->i++];
    if (word[data->i] == '\'')
        data->i++;
    else
        free_all(data, 0,  "Error\nQuotes aren't closed");
    return (j);
}

static int	ft_handle_dquotes(char *res, int j, char *word, t_data *data)
{
    data->i++;
    while (word[data->i] && word[data->i] != '"')
    {
        if (word[data->i] == '$')
            j = ft_expand_var(res, j, word, data);
        else
            res[j++] = word[data->i++];
    }
    if (word[data->i] == '"')
	{
		if (j == 0)
			res[j++] = '$';
        data->i++;
	}
    else
        free_all(data, 0, "Error\nQuotes aren't closed");
    return (j);
}

static char	*ft_expand_word(t_data *data, char *word)
{
    char	res[4096];
    int		j;

    j = 0;
	data->i = 0;
    while (word[data->i])
    {
        if (word[data->i] == '\'')
            j = ft_handle_squotes(res, j, word, data);
        else if (word[data->i] == '"')
            j = ft_handle_dquotes(res, j, word, data);
		else if (word[data->i] == '$')
            j = ft_expand_var(res, j, word, data);
        else
            res[j++] = word[data->i++];
    }
    res[j] = '\0';
    return (ft_strdup(res));
}

void expand_exec_list(t_data *data)
{
    char    *new_word;
    t_exec  *exec;
	int i;

    exec = data->exec;
    while (exec)
    {
        i = 0;
        while (exec->cmd && exec->cmd[i])
        {
            new_word = ft_expand_word(data, exec->cmd[i]);
            if (new_word)
            {
                free(exec->cmd[i]);
                exec->cmd[i] = new_word;
            }
			else
				free_all(data, 0, "Error\nMalloc fail in ft_expand_word");
            i++;
        }
        exec = exec->next;
    }
}

/*
	- ne pas gerer $$ ($$HOME, $$, $$PWD ...) OK 
	- tout me semble ok, a refacto pour la norme
	- exit sur quote pas fermer
	- ne pas expand les strings de la value de variable OK
	- dans le cas de : $fdjfds ls -> expand resulte d'un NULL et ls est considere comme l'argument, mais ls doit etre executer
	                    CMD    ARGS
*/