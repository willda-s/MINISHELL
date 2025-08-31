#include "builtins.h"

static int  parsing_export(t_exec *exec)
{
    int i;

    i = 0;
    while (exec->cmd[1][i])
    {
        if (!ft_isalnum(exec->cmd[1][i]) && exec->cmd[1][i] != '=')
            return (1);
        i++;
    }
    return (0);
}

static t_env  *extract_key_value(t_exec *exec)
{
    int     i;
    int     j;
    char    *key;
    char    *value;
    t_env   *env;

    i = 0;
    j = 0;
    key = malloc(256);
    value = malloc(256);
    env = malloc(sizeof(t_env));
    
    while (exec->cmd[1][i] && exec->cmd[1][i] != '=')
    {
        key[i] = exec->cmd[1][i];
        i++;
    }
    key[i] = '\0';
    
    if (exec->cmd[1][i] == '=')
    {
        i++;
        while (exec->cmd[1][i])
        {
            value[j] = exec->cmd[1][i];
            i++;
            j++;
        }
    }
    value[j] = '\0';
    
    env->key = key;
    env->value = value;
    env->next = NULL;
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
    if (!exec->cmd[1])
        builtin_env(exec->env);
    else
    {
        t_env *new_var = extract_key_value(exec);
        ft_lstlast_env(exec->env)->next = new_var;
    }
    return (0);
}
