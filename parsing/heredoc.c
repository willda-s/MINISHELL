/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:57:53 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/04 18:32:20 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"
#include "libft.h"
#include "parsing.h"
#include <errno.h>

char	*file_create(int i)
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
	char	*line;

	while (1)
	{
		line = readline("Heredoc> ");
		if (!line)
			break ;
		if (line && ft_strcmp(line, redir->delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_dprintf(fd[1], "%s\n", line);
		free(line);
	}
}

static void	open_heredoc_out(t_redir *redir, t_data *data, int i)
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

void	handle_heredoc(t_data *data)
{
	t_exec	*tmp;
	t_redir	*redir;
	int		i;

	tmp = data->exec;
	redir = NULL;
	i = 0;
	while (tmp)
	{
		redir = tmp->redir;
		while (redir)
		{
			if (redir->delimiter)
			{
				open_heredoc_out(redir, data, i);
				i++;
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}

int	handle_errcode(char *res, int j, t_data *data)
{
	int		len;
	char	*str;

	str = ft_itoa(data->errcode);
	len = 0;
	while (res && str && str[len])
		res[j++] = str[len++];
	free(str);
	data->i++;
	return (j);
}
