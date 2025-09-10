
#include "fd_printf.h"
#include "parsing.h"
#include "signals.h"
#include <readline/history.h>
#include <readline/readline.h>

volatile sig_atomic_t	g_signal_status = 0;

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
		setup_main_signals();
		while (1)
		{
			data.input = readline("minishell> ");
			if (!data.input)
			{
				ft_dprintf(2, "exit\n");
				free_lst_env(&envd, false, 0);
				return (g_signal_status);
			}
			if (*data.input)
				add_history(data.input);
			data.input = check_input(data.input);
			if (!data.input)
			{
				free_lst_env(&envd, false, 0);
				continue ;
			}
			dst = ft_split_with_quotes(data.input, ' ');
			if (!dst)
				free_lst_env(&envd, true, 0);
			init_data(&data, &envd, dst);
			token_main(&data);
			// if (data.pars && validate_syntax(data.pars))
			// {
			// 	g_signal_status = 2;
			// 	free_tmpall(&data);
			// 	continue ;
			// }
			init_lst_exec(&data);
			if (expand_exec_list(&data) != 0)
				continue ;
			init_envp(&data);
			remove_empty_line(&data);
			print_lst_exec(data.exec);
			print_lst_pars(data.pars);
			// handle_heredoc(&data);
			if (g_signal_status == 130)
				g_signal_status = 0;
			// execc(&data);
			free_tmpall(&data);
		}
	}
	return (g_signal_status);
}

// int	main(int ac, char **av)
// {
// 	char	*result;

// 	// size_t	space_count;
// 	// size_t	i;
// 	result = NULL;
// 	// i = 0;
// 	// space_count = 0;
// 	if (ac == 2)
// 	{
// 		result = check_input(av[1]);
// 		// while (result[i])
// 		// {
// 		// 	if (ft_strcmp(&result[i], " ") == 0)
// 		// 		++space_count;
// 		// 	++i;
// 		// }
// 		// printf("count =%zu\n", space_count);
// 		printf("%s\n", result);
// 	}
// 	return (0);
// }

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

			REGLER INPUT_CHECK LORSQUE ECHO QVEC " "

*/
