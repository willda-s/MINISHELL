
#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

int	main(int ac, char **av, char **env)
{
	char	**dst;
	t_env	*envd;
	t_data	data;

	(void)ac;
	(void)av;
	if (ac == 1)
	{
		envd = NULL;
		init_lst_env(&envd, env);
		init_sigint();
		while (1)
		{
			if (isatty(fileno(stdin)))
				data.input = readline("> ");
			else
			{
				char *line;
				line = get_next_line(fileno(stdin));
				data.input = ft_strtrim(line, "\n");
				free(line);
			}
			// data.input = readline("minishell> ");
			if(!data.input)
				return (data.errcode);
			if (*data.input)
				add_history(data.input);
			data.input = check_input(data.input);
			if (!data.input)
				free_lst_env(&envd, false, 0);
			dst = ft_split_with_quotes(data.input, ' ');
			if (!dst)
			{
				free(data.input);
				free_lst_env(&envd, true, 0);
			}
			init_data(&data, &envd, dst);
			token_main(&data);
			if (data.pars && validate_syntax(data.pars))
			{
				free_tmpall(&data);
				continue ;
			}
			init_lst_exec(&data);
			expand_exec_list(&data);
			init_envp(&data);
			// remove_empty_line(&data);
			// print_lst_exec(data.exec);
			// print_lst_pars(data.pars);
			handle_heredoc(&data);
			execc(&data);
			free_tmpall(&data);
		}
	}
}



/*TO DO :
			- expand vide dans le cas du token=commands alors pas d'execution
			- handle builtins dans exec
			- $? et code de sortie
			- signal
*/

/*A SUPPRIMER DU .H ET DU .C :
			- print_lst_env(t_env *envd);
			- print_envp(char **envp);
			- Function_print.c
			- print_lst_exec(data.exec);
			- print_lst_pars(data.pars);
			- remove_empty_line.c
*/
