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

static int	wait_process(int pid)
{
	int		count;
	int		pid_w;
	int		status;
	int		err;
	size_t	i;

	count = 2;
	i = 0;
	while (count--)
	{
		pid_w = wait(&status);
		if (pid_w == -1)
			exit(errno);
		else if (pid == pid_w && WIFEXITED(status))
			err = WEXITSTATUS(status);
		i++;
	}
	return (err);
}


pid_t execfirstcmd(t_data *data, int *fd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		open_dup_close_firstcmd(data, fd);
		data->exec->path = path_in_arg(data->exec);
		if (data->exec->path == NULL)
			data->exec->path = find_path(data);
		if (data->exec->path != NULL)
			execve(data->exec->path, data->exec->cmd, data->envp);
	}
	return (pid);
}

pid_t execlastcmd(t_data *data, int *fd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		printf("salut");
		open_dup_close_lastcmd(data, fd);
		data->exec->path = path_in_arg(data->exec);
		if (data->exec->path == NULL)
			data->exec->path = find_path(data);
		if (data->exec->path != NULL)
			execve(data->exec->path, data->exec->cmd, data->envp);
	}
	return (pid);
}
void execc(t_data *data)
{
	int		pid;
	int		err;
	int		fd[2];

	err = 0;
	if (data->exec->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe firstcmd");
			exit(errno);
		}
	}
		pid = execfirstcmd(data, fd);
		if (data->exec->next)
		{
			data->exec = data->exec->next;
			pid = execlastcmd(data, fd);
		}
		err = wait_process(pid);
}