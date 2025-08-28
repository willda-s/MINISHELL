#include "builtins.h"

int builtin_echo(t_exec *exec)
{
    int i;
    int new_line;

    i = 1;
    new_line = 1;
    //cas de l option -n
    if (exec->cmd[1] && ft_strncmp(exec->cmd[1], "-n", 2) == 0)
    {
        i = 2;
        new_line = 0;
    }
    //parcourt des arguments de la commande
    while (exec->cmd[i])
    {
        write(exec->fd_out, exec->cmd[1], ft_strlen(exec->cmd[1]));
        if (exec->cmd[i + 1])
            write(exec->fd_out, " ", 1);
        i++;
    }
    if (new_line)
        write(exec->fd_out, "\n", 1);
    return (0);
}
