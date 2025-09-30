/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 23:56:37 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/30 22:02:01 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "libft.h"
#include "parsing.h"
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

static char	*file_create(int i);
static void	write_in_heredoc(int *fd, t_redir *redir);
static int	get_random_int(t_data *data);

void	open_heredoc_out(t_redir *redir, t_data *data)
{
	int		fd[2];
	char	*file;

	file = file_create(get_random_int(data));
	if (!file)
		free_all(data, true, 1);
	fd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd[1] == -1)
	{
		ft_dprintf(2, "Heredoc: %s\n", strerror(errno));
		free(file);
		free_all(data, true, 1);
	}
	write_in_heredoc(fd, redir);
	redir->filename = ft_strdup(file);
	close(fd[1]);
	free(file);
	if (!redir->filename)
		free_all(data, true, 1);
}

static char	*file_create(int i)
{
	static const char	*tmpfile;
	char				*index;
	char				*buffer;

	tmpfile = "/tmp/heredoc";
	index = ft_itoa(i);
	if (!index)
		return (NULL);
	buffer = ft_strjoin(tmpfile, index);
	free(index);
	if (!buffer)
		return (NULL);
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

static int	get_random_int(t_data *data)
{
	int	rng;
	int	fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		free_all(data, true, 1);
	if (read(fd, &rng, sizeof(rng)) == -1)
		free_all(data, true, 1);
	if (close(fd) == -1)
		free_all(data, true, 1);
	return (rng);
}
