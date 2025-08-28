#include "builtins.h"

int get_output_fd(t_exec *exec)
{
    int output_fd;

    if (exec->fd_out == -1)
        output_fd = STDOUT_FILENO;
    else
        output_fd = exec->fd_out;
    return (output_fd);
}
