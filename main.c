/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:55:40 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/13 05:57:09 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "get_next_line_bonus.h"
#include "libft.h"
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
	// char	*line;

	(void)ac;
	(void)av;
	if (ac == 1)
	{
		envd = NULL;
		init_lst_env(&envd, env);
		setup_main_signals();
		while (1)
		{
			// if (isatty(fileno(stdin)))
			// 	data.input = readline("minishell> ");
			// else
			// {
			// 	line = get_next_line(fileno(stdin));
			// 	if (!line)
			// 	{
			// 		free_lst_env(&envd, false, 0);
			// 		return (g_signal_status);
			// 	}
			// 	data.input = ft_strtrim(line, "\n");
			// 	free(line);
			// }
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
			{
				free(data.input);
				free_lst_env(&envd, true, 0);
			}
			init_data(&data, &envd, dst);
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
			remove_empty_line(&data);
			// print_lst_exec(data.exec);
			// print_lst_pars(data.pars);
			handle_heredoc(&data);
			if (g_signal_status == 130)
				g_signal_status = 0;
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

			!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  ECHO ET TOUS LES AUTRES BUILTINS DANS REDIRECTION AVOIR UN FD TOUJOURS SUR 1 A PART SI REDIR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

*/
