
#include "parsing.h"

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
		if (!input)
		{
			ft_putstr_fd("exit\n", 2);
			free_lst_env(&envd, true, 0);
		}
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
		// print_lst_exec(data.exec);
		// print_lst_pars(data.pars);
		handle_heredoc(&data);
		execc(&data);
		// ft_dprintf(2, "%d\n", data.errcode);
		free_tmpall(&data);
	}
}

/*TO DO :
			- heredoc
			- $? et code de sortie
			- redirection files
			- signal
*/

/*A SUPPRIMER DU .H ET DU .C :
			- print_lst_env(t_env *envd);
			- print_envp(char **envp);
			- Function_print.c
			- print_lst_exec(data.exec);
			- print_lst_pars(data.pars);

*/
