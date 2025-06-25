
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
	init_duplicate_env(&envd, env);
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
		// handle_quotes(&data);
		expand_exec_list(data.exec, data.env);
		print_lst_exec(data.exec);
		print_lst_pars(data.pars);
		// free_all(&data, dst);
	}
}

//TOUTES LES REMONTES D'ERREUR A VERIFIER
//gerer les quotes ouvert fermes + expand ce qui ya dedans

//Le premier mot entre chaque pipe est forcement une commande

/*TO DO : 
	- Finir token avec builtins
	- initialiser char **envp (t_data)
*/