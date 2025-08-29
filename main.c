
#include "parsing.h"
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
	if (ac == 1)
	{
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
			if (data.pars && validate_syntax(data.pars))
			{
				free_all(&data, 2, "");
				return (-1);
			}
			print_lst_exec(data.exec);
			print_lst_pars(data.pars);
			free_all(&data, 0, "");
		}
	}
}


/*TO DO :
	LE PARSING SEMBLE FINIT, NORMER, SECURISER.

			- REPRENDRE LE HEREDOC
			-  SIGNAUX
*/

/*A SUPPRIMER DU .H ET DU .C :
			- print_lst_env(t_env *envd);
			- print_envp(char **envp);
			- Function_print.c
			- print_lst_exec(data.exec);
			- print_lst_pars(data.pars);

*/
