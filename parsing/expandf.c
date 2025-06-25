#include "../includes/parsing.h"

static int	ft_expand_var(char *res, int j, char *word, int *i, t_env *env)
{
    char	var[256];
    char	*val;
    int		k;

    (*i)++;
    k = 0;
    while (word[*i] && is_var_char(word[*i]) && word[*i] != '"' && word[*i] != '\'' && k < 255)
        var[k++] = word[(*i)++];
    var[k] = '\0';
    val = get_env_value(env, var);
    k = 0;
    while (val && val[k])
        res[j++] = val[k++];
    return (j);
}

static int	ft_handle_squotes(char *res, int j, char *word, int *i)
{
    (*i)++;
    while (word[*i] && word[*i] != '\'')
        res[j++] = word[(*i)++];
    if (word[*i] == '\'')
        (*i)++;
    return (j);
}

static int	ft_handle_dquotes(char *res, int j, char *word, int *i, t_env *env)
{
    (*i)++;
    while (word[*i] && word[*i] != '"')
    {
        if (word[*i] == '$')
            j = ft_expand_var(res, j, word, i, env);
        else
            res[j++] = word[(*i)++];
    }
    if (word[*i] == '"')
        (*i)++;
    return (j);
}

static char	*ft_expand_word(t_env *env, char *word)
{
    char	res[4096];
    int		i;
    int		j;

    i = 0;
    j = 0;
    while (word[i])
    {
        if (word[i] == '\'')
            j = ft_handle_squotes(res, j, word, &i);
        else if (word[i] == '"')
            j = ft_handle_dquotes(res, j, word, &i, env);
        else if (word[i] == '$')
            j = ft_expand_var(res, j, word, &i, env);
        else
            res[j++] = word[i++];
    }
    res[j] = '\0';
    return (ft_strdup(res));
}

void	expand_exec_list(t_exec *exec, t_env *env)
{
    int		i;
    char	*new_word;

    while (exec)
    {
        i = 0;
        while (exec->cmd && exec->cmd[i])
        {
            new_word = ft_expand_word(env, exec->cmd[i]);
            if (new_word)
            {
                free(exec->cmd[i]);
                exec->cmd[i] = new_word;
            }
            i++;
        }
        exec = exec->next;
    }
}

