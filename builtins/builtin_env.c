#include "builtins.h"

int builtin_env(t_env *env)
{
    t_env *tmp = env;

    while (tmp)
    {
        if (tmp->value)
        {
            write(1, tmp->key, ft_strlen(tmp->key));
            write(1, "=", 1);
            write(1, tmp->value, ft_strlen(tmp->value));
            write(1, "\n", 1);
        }
        tmp = tmp->next;
    }
    return (0);
}
