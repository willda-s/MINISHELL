/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:07:45 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/31 00:01:32 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
 
static int	wait_process(int nb_proc)
{
	int		pid_w;
	int		status;
	int		err = 0;
	int		count = 0;

	while (count < nb_proc)
	{
		pid_w = wait(&status);
		if (pid_w == -1)
			exit(errno);
		if (WIFEXITED(status))
			err = WEXITSTATUS(status);
		count++;
	}
	return (err);
}

void exec_cmd(t_exec *node, t_data *data)
{
	if (node->cmd)
	{
		node->path = path_in_arg(node);
		if (node->path == NULL)
			node->path = find_path(node, data);
		if (node->path != NULL)
            execve(node->path, node->cmd, data->envp);
			ft_dprintf(2, "%s: command not found\n", node->cmd[0]);
	}	
	close_allfd_struct(data);
	free_all(data, 127, "", true);
}

void init_pipe(t_exec *node)
{
    int fd[2];
	t_exec  *next = node->next;

    if (pipe(fd) == -1)
        exit(errno);
    node->fd_out = fd[1];
    next->fd_in = fd[0];
}

void execc(t_data *data)
{
	t_exec	*tmp = data->exec;
	t_exec	*prev = NULL;

	int	i = 0;
	while (tmp)
	{
		if (tmp->next)
			init_pipe(tmp);
		pid_t pid = fork();
		if (pid == 0)
		{
			dup_fd(tmp, data);
			close_last_fd(prev);
			exec_cmd(tmp, data);
		}
		else if (pid < 0)
			free_all(data, errno, "fork fail\n", true); //errno 12 = malloc fail ?
		close_fd(tmp);
		i++;
		prev = tmp;
		tmp = tmp->next;
	}
    data->errcode = wait_process(i); //on recup le dernier code d'erreur sur data->errcode ?
}
