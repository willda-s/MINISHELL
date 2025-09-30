/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:13:35 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 22:49:29 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "signals.h"
#include <readline/history.h>
#include <readline/readline.h>
#include "ft_dprintf.h"

int	handle_input(t_data *data)
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

int	process_input(t_data *data)
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

int	handle_parsing(t_data *data)
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

int	handle_exec(t_data *data)
{
	int	expand_res;

	init_lst_exec(data);
	expand_res = expand_exec_list(data);
	if (expand_res != 0)
		return (expand_res);
	init_envp(data);
	handle_heredoc(data);
	exec(data);
	return (0);
}
