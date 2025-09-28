/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 23:43:26 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/28 03:03:35 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"
#include "signals.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>

volatile sig_atomic_t	g_signal_status = 0;

static int				main_loop(t_data *data);
static int				handle_input(t_data *data);
static int				process_input(t_data *data);
static int				handle_parsing(t_data *data);
static int				handle_exec(t_data *data);

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		loop_res;

	(void)ac;
	(void)av;
	loop_res = 0;
	ft_bzero(&data, sizeof(t_data));
	if (ac == 1)
	{
		init_lst_env(&data.env, env);
		setup_main_signals();
		loop_res = main_loop(&data);
		if (loop_res == -1)
		{
			data.errcode = 0;
			return (data.errcode);
		}
	}
	return (data.errcode);
}

static int	main_loop(t_data *data)
{
	int	res;

	res = 0;
	while (1)
	{
		data->syntax_error_flag = 0;
		res = handle_input(data);
		if (res == -1)
			return (res);
		if (process_input(data))
			continue ;
		if (handle_parsing(data))
			continue ;
		if (handle_exec(data))
			continue ;
		free_tmpall(data);
	}
	return (0);
}

static int	handle_input(t_data *data)
{
	data->input = readline("minishell> ");
	if (!data->input)
	{
		ft_dprintf(2, "exit\n");
		rl_clear_history();
		free_all(data, true, 131);
		return (-1);
	}
	if (*data->input)
		add_history(data->input);
	return (0);
}

static int	process_input(t_data *data)
{
	char	**dst;
	char	*original_input;

	original_input = data->input;
	data->input = check_input(data->input);
	free(original_input);
	if (!data->input)
	{
		free_lst_env(&data->env, false, 0);
		return (1);
	}
	dst = ft_split_with_quotes(data->input, ' ');
	if (!dst)
	{
		free(data->input);
		free_lst_env(&data->env, true, 0);
		return (-1);
	}
	init_data(data, &data->env, dst);
	return (0);
}

static int	handle_parsing(t_data *data)
{
	token_main(data);
	if (data->pars && validate_syntax(data->pars))
	{
		g_signal_status = 2;
		free_tmpall(data);
		return (2);
	}
	return (0);
}

static int	handle_exec(t_data *data)
{
	int	expand_res;

	init_lst_exec(data);
	expand_res = expand_exec_list(data);
	if (expand_res != 0)
		return (expand_res);
	init_envp(data);
	handle_heredoc(data);
	execc(data);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	char	**dst;
// 	t_data	data;

// 	ft_bzero(&data, sizeof(t_data));
// 	(void)ac;
// 	(void)av;
// 	data.env = NULL;
// 	if (ac == 1)
// 	{
// 		init_lst_env(&data.env, env);
// 		setup_main_signals();
// 		while (1)
// 		{
// 			data.syntax_error_flag = 0;
// 			data.input = readline("minishell> ");
// 			if (!data.input)
// 			{
// 				ft_dprintf(2, "exit\n");
// 				rl_clear_history();
// 				free_all(&data, true, 12);
// 			}
// 			if (*data.input)
// 				add_history(data.input);
// 			data.input = check_input(data.input);
// 			if (!data.input)
// 			{
// 				free_lst_env(&data.env, false, 0);
// 				continue ;
// 			}
// 			dst = ft_split_with_quotes(data.input, ' ');
// 			if (!dst)
// 			{
// 				free(data.input);
// 				free_lst_env(&data.env, true, 0);
// 			}
// 			init_data(&data, &data.env, dst);
// 			token_main(&data);
// 			if (data.pars && validate_syntax(data.pars))
// 			{
// 				g_signal_status = 2;
// 				free_tmpall(&data);
// 				continue ;
// 			}
// 			init_lst_exec(&data);
// 			if (expand_exec_list(&data) != 0)
// 				continue ;
// 			init_envp(&data);
// 			// remove_empty_line(&data);
// 			// print_lst_exec(data.exec);
// 			// print_lst_pars(data.pars);
// 			handle_heredoc(&data);
// 			execc(&data);
// 			free_tmpall(&data);
// 		}
// 	}
// 	return (data.errcode);
// }

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

			EXPORT/UNSET ONLY 1ST VALUE
			export t ------> t=      (not good)
*/
