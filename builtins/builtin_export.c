#include "builtins.h"

static int  parsing_export(t_exec *exec)
{
    int i;

    i = 0;
    while (exec->cmd[i])
    {
        if (!is_alphanum(exec->cmd[i]))
            return (1);
        i++;
    }
    return (0);
}

int builtin_export(t_exec *exec)
{
    if (parsing_export(exec))
        return (1);
    //...
    return (0);
}
