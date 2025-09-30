/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 23:43:26 by willda-s          #+#    #+#             */
/*   Updated: 2025/10/01 00:10:47 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"
#include "signals.h"
#include <readline/history.h>
#include <readline/readline.h>

volatile sig_atomic_t	g_signal_status = 0;

static int				main_loop(t_data *data);

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
