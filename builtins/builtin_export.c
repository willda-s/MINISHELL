#include "builtins.h"

static int  parsing_export(t_exec *exec)
{
    int i;

    i = 0;
    while (exec->cmd[1][i])
    {
        if (!is_alphanum(exec->cmd[1][i]) && exec->cmd[1][i] != '=')
            return (1);
        i++;
    }
    return (0);
}

static t_env  extract_key_value(t_exec *exec)
{
    int     i;
    int     j;
    char    *key;
    char    *value;
    t_env   env;

    i = 0;
    j = 0;
    value = "";
    while (exec->cmd[1][i] && exec->cmd[1][i] != '=')
    {
        key[i] = cmd[1][i];
        i++;
    }
    if (exec->cmd[1][i] == '=')
        i++;
    while (exec->cmd[1][i++])
    {
        value[j] = cm[1][i];
        j++;
    }
    return (env);
}

int builtin_export(t_exec *exec)
{
    if (parsing_export(exec))
        return (1);
    //etape 1 : trouver la pos pour ajouter la var
    //etape 2 :
        //cas 1 : export sans arg -> afficher l env
        //cas 2 : export + 1 arg -> ajouter a l env
        //cas 3 : export + 2 args -> ajouter a l env + assigner value
    if (!cmd[2])
        builtin_env(exec);
    else
        ft_lstlast_env(extract_key_value(exec));
    return (0);
}
