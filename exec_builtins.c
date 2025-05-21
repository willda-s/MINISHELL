
#include "builtins.h"

void	exec_builtins(char **str, char **env, char *input)
{
	if (ft_strncmp(str[0], "env", 3) == 0 && ft_strlen(str[0]) == 3)
		ft_env(env);
	else if (ft_strncmp(str[0], "pwd", 3) == 0 &&  ft_strlen(str[0]) == 3)
		ft_pwd();
	else if (ft_strncmp(str[0], "exit", 4) == 0 && ft_strlen(str[0]) == 4)
	{
		errno = ft_exit(str);
		if (errno != -12)
		{
			free(input);
			free_tab(str);
			exit(errno);
		}
	}
	else if (ft_strncmp(str[0], "echo", 4) == 0 &&  ft_strlen(str[0]) == 4)
		ft_echo(str);
	else if (ft_strncmp(str[0], "cd", 2) == 0 && ft_strlen(str[0]) == 2)
		ft_cd(str);
	else if (ft_strncmp(str[0], "export",6) == 0 &&  ft_strlen(str[0]) == 6)
		ft_export(str, env);
	else if (ft_strncmp(str[0], "unset", 5) == 0 &&  ft_strlen(str[0]) == 5)
		ft_unset(str, env);
	else
	{
		printf("bash %s: command not found\n", input);
		errno = 127;
	}
}
