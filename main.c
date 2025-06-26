
#include "includes/parsing.h"
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *input;
	char **dst;
	t_env 	*envd;
	t_data	data;

	envd = NULL;
	init_lst_env(&envd, env);
	while (1)
	{
		input = readline("> ");
		if (*input)
			add_history(input);
		dst = ft_split_with_quotes(input, ' ');
		if (!dst)
			free_lst_env(&envd);
		if (init_data(&data, &envd, dst) == 1)
			free_all(&data, dst);
		token_main(&data.pars);
		init_lst_exec(&data.exec, data.pars);
		expand_exec_list(data.exec, data.env);
		init_envp(&data);
		// print_envp(data.envp);
		print_lst_exec(data.exec);
		print_lst_pars(data.pars);
		// free_all(&data, dst);
	}
}


/*TO DO :
 			-TOUTES LES REMONTES D'ERREUR A VERIFIER
			-REFACTO EXPAND
			
*/