
#include "includes/env.h"
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env 	*envd;

	envd = NULL;
	init_duplicate_env(&envd, env);
	free_lst_env(&envd);
}

//split with quotes