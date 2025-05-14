
#include "builtins.h"

int ft_cd(char **str) // Prototypage qui sera changer par la suite. SECURE A FAIRE
{
    char *path;
    int ret;
	size_t limit;

    limit = 255;
    if (str[1] == NULL || ft_strncmp(str[1], "~", 1) == 0)
    {
        path = getenv("HOME");
        if (path == NULL)
            return (1);
    }
    else
        path = str[1];
    if (ft_strlen(path) > limit)
    {
        printf("cd: %s: File too long\n", path);
        return (1);
    }
    ret = chdir(path);
    if (ret == -1)
    {
        perror("cd");
        return (1);
    }
    return (0);
}
