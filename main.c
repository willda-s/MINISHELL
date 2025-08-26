#include "../includes/minishell.h"
// #include "exec.h"
#include <readline/history.h>
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
			free_lst_env(&envd, true, 0);
		init_data(&data, &envd, dst);
		token_main(&data);
		init_lst_exec(&data);
		expand_exec_list(&data);
		init_envp(&data);
		remove_empty_line(&data);
		exec_cmd(&data);
		print_lst_exec(data.exec);
		print_lst_pars(data.pars);
		//free_all(&data, 0, "");
	}
}


// TOUTES LES REMONTES D'ERREUR A VERIFIER
// gerer les quotes ouvert fermes + expand ce qui ya dedans

// Le premier mot entre chaque pipe est forcement une commande

/*TO DO :
	- Finir token avec builtins
	- initialiser char **envp (t_data)
*/