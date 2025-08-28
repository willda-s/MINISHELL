#include "builtins.h"

int  builtin_unset(char *var, t_env **env)
{
    t_env *current = *env;
    t_env *prev = NULL;
    if (current != NULL && strcmp(current->key, var) == 0)
    {
        env = current->next;
        free(current->key);
        free(current->value);
        free(current);
        return (0);
    }
    while (current != )
}
