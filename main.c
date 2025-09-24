/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 23:43:26 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/24 02:17:17 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_dprintf.h"
#include "parsing.h"
#include "signals.h"
#include <readline/history.h>
#include <readline/readline.h>

volatile sig_atomic_t	g_signal_status = 0;

int	main(int ac, char **av, char **env)
{
	char	**dst;
	// t_env	*envd;
	t_data	data;
	// char	*line;

	(void)ac;
	(void)av;
	data.env = NULL;
	if (ac == 1)
	{
		// envd = NULL;
		init_lst_env(&data.env, env);
		setup_main_signals();
		while (1)
		{
			data.input = readline("minishell> ");
			if (!data.input)
			{
				ft_dprintf(2, "exit\n");
				rl_clear_history();
				free_all(&data, 12);
				return (g_signal_status);
			}
			if (*data.input)
				add_history(data.input);
			data.input = check_input(data.input);
			if (!data.input)
			{
				free_lst_env(&data.env, false, 0);
				continue ;
			}
			dst = ft_split_with_quotes(data.input, ' ');
			if (!dst)
			{
				free(data.input);
				free_lst_env(&data.env, true, 0);
			}
			init_data(&data, &data.env, dst);
			token_main(&data);
			if (data.pars && validate_syntax(data.pars))
			{
				g_signal_status = 2;
				free_tmpall(&data);
				continue ;
			}
			init_lst_exec(&data);
			if (expand_exec_list(&data) != 0)
				continue ;
			init_envp(&data);
			// remove_empty_line(&data);
			// print_lst_exec(data.exec);
			// print_lst_pars(data.pars);
			handle_heredoc(&data);
			execc(&data);
			free_tmpall(&data);
		}
	}
	return (g_signal_status);
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

			REGLER INPUT_CHECK LORSQUE ECHO QVEC " "
			- EXIT CODE

			!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  ECHO ET TOUS LES AUTRES BUILTINS DANS REDIRECTION AVOIR UN FD TOUJOURS SUR 1 A PART SI REDIR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

*/
