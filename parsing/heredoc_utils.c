/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 23:56:37 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/12 23:59:03 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"
#include "signals.h"
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

static char	*file_create(int i);
static void	write_in_heredoc(int *fd, t_redir *redir);
static void	heredoc_child_loop(int *fd, t_redir *redir);

int	handle_errcode(char *res, int j)
{
	char	*str;
	size_t	i;
	size_t	len;

	str = ft_itoa(g_signal_status);
	if (!str)
		return (j);
	len = ft_strlen(str);
	i = 0;
	while (i < len)
		res[j++] = str[i++];
	free(str);
	return (j);
}

void	open_heredoc_out(t_redir *redir, t_data *data, int i)
{
	int		fd[2];
	char	*file;

	file = file_create(i);
	fd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd[1] == -1)
	{
		ft_dprintf(2, "Heredoc: %s\n", strerror(errno));
		free_all(data, 1);
	}
	write_in_heredoc(fd, redir);
	redir->filename = ft_strdup(file);
	close(fd[1]);
	free(file);
}

static char	*file_create(int i)
{
	char	*tmpfile;
	char	*index;
	char	*buffer;

	tmpfile = "/tmp/heredoc";
	index = ft_itoa(i);
	buffer = ft_strjoin(tmpfile, index);
	free(index);
	return (buffer);
}

static void	write_in_heredoc(int *fd, t_redir *redir)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		heredoc_child_loop(fd, redir);
	else
	{
		setup_parent_signals();
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_signal_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_signal_status = 128 + WTERMSIG(status);
		setup_main_signals();
	}
}

static void	heredoc_child_loop(int *fd, t_redir *redir)
{
	char	*line;

	setup_heredoc_signals();
	while (1)
	{
		line = readline("Heredoc> ");
		if (!line)
		{
			g_signal_status = 130;
			exit(130);
		}
		if (line && ft_strcmp(line, redir->delimiter) == 0)
		{
			free(line);
			exit(0);
		}
		ft_dprintf(fd[1], "%s\n", line);
		free(line);
	}
}
