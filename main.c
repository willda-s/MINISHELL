
#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

int	main(int ac, char **av, char **env)
{
	char	*input;
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
			input = readline("minishell> ");
			if (*input)
				add_history(input);
			input = check_input(input);
			if (!input)
			{
				free_lst_env(&envd, true, 0);
				return (-1);
			}
			if (*input == '\0')
			{
				free_lst_env(&envd, true, 0);
				continue ;
			}
			dst = ft_split_with_quotes(input, ' ');
			if (!dst)
				free_lst_env(&envd, true, 0);
			init_data(&data, &envd, dst);
			token_main(&data);
			if (data.pars && validate_syntax(data.pars))
			{
				free_all(&data, 2);
				continue ;
			}
			init_lst_exec(&data);
			expand_exec_list(&data);
			init_envp(&data);
			remove_empty_line(&data);
			print_lst_exec(data.exec);
			print_lst_pars(data.pars);
			free_all_msg(&data, 0, "");
		}
	}
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
