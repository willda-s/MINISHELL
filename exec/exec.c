/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:12:50 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/27 23:12:39 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	wait_process(int nb_proc, int last_pid)
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
		if (last_pid == pid_w && WIFEXITED(status))
			err = WEXITSTATUS(status);
		count++;
	}
	return (err);
}


pid_t execfirstcmd(t_data *data, int *fd)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		open_dup_close_firstcmd(data, fd);
		data->exec->path = path_in_arg(data->exec);
		if (data->exec->path == NULL)
			data->exec->path = find_path(data);
		if (data->exec->path != NULL)
			execve(data->exec->path, data->exec->cmd, data->envp);
		free_all(data, errno, "execve", true);
	}
	return (pid);
}

pid_t execlastcmd(t_data *data, int *fd)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		open_dup_close_lastcmd(data, fd);
		data->exec->path = path_in_arg(data->exec);
		if (data->exec->path == NULL)
			data->exec->path = find_path(data);
		if (data->exec->path != NULL)
			execve(data->exec->path, data->exec->cmd, data->envp);
		free_all(data, errno, "execve", true);
	}
	return (pid);
}
void execc(t_data *data)
{
	int		pid1 = -1;
	int		pid2 = -1;
	int		fd[2];
	t_exec	*save = data->exec;

	if (data->exec->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe firstcmd");
			exit(errno);
		}
		pid1 = execfirstcmd(data, fd);
		close(fd[1]);
		data->exec = data->exec->next;
		pid2 = execlastcmd(data, fd);
		close(fd[0]);
		wait_process(2, pid2);
		data->exec = save;
	}
	else
	{
		pid1 = execfirstcmd(data, NULL);
	   wait_process(1, pid1);
	}
}