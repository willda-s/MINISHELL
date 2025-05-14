
#include "builtins.h"

void	exec_builtins(char **str, char **env, char *input)
{
	if (ft_strncmp(str[0], "env", ft_strlen(str[0])) == 0)
		ft_env(env);
	else if (ft_strncmp(str[0], "pwd", ft_strlen(str[0])) == 0)
		ft_pwd();
	else if (ft_strncmp(str[0], "exit", ft_strlen(str[0])) == 0)
	{
		errno = ft_exit(str);
		if (errno != -12)
		{
			free(input);
			free_tab(str);
			exit(errno);
		}
	}
	else if (ft_strncmp(str[0], "echo", ft_strlen(str[0])) == 0)
		ft_echo(str);
	else if (ft_strncmp(str[0], "cd", ft_strlen(str[0])) == 0)
		ft_cd(str);
	else if (ft_strncmp(str[0], "export", ft_strlen(str[0])) == 0)
		ft_export(str, env);
	else if (ft_strncmp(str[0], "unset", ft_strlen(str[0])) == 0)
		ft_unset(str, env);
}
