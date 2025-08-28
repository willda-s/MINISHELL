#include "builtins.h"

int builtin_pwd(t_exec *exec)
{
    char    *cwd;
    int     output_fd;

    output_fd = get_output_fd(exec);
    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("pwd");
        return (1);
    }
    write(output_fd, cwd, ft_strlen(cwd));
    write(output_fd, "\n", 1);
    free(cwd);
    return (0);
}
