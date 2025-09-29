/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 23:43:26 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/29 23:08:32 by akarapkh         ###   ########.fr       */
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
