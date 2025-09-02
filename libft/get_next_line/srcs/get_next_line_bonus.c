/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 05:25:47 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/02 17:17:14 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "vectors.h"
#include "libft.h"

static ssize_t	process_line_with_newline(char buffer[MAX_FD][BUFFER_SIZE + 1],
		int fd, t_vector *line_vector)
{
	char	*newline_pos;
	size_t	line_len;
	size_t	i;

	if (!buffer || !line_vector || fd < 0 || fd >= MAX_FD)
		return (-1);
	newline_pos = ft_strchr(buffer[fd], '\n');
	if (!newline_pos)
		return (0);
	line_len = newline_pos - buffer[fd] + 1;
	i = 0;
	while (i < line_len)
	{
		if (add_vector(line_vector, &buffer[fd][i], 1) == -1)
			return (-1);
		i++;
	}
	ft_memmove(buffer[fd], newline_pos + 1, ft_strlen(newline_pos + 1) + 1);
	return (1);
}

static ssize_t	process_line_without_newline(char buffer[MAX_FD][BUFFER_SIZE
		+ 1], int fd, t_vector *line_vector)
{
	size_t	i;

	if (!buffer || !line_vector || fd < 0 || fd >= MAX_FD)
		return (-1);
	i = 0;
	while (buffer[fd][i])
	{
		if (add_vector(line_vector, &buffer[fd][i], 1) == -1)
			return (-1);
		i++;
	}
	buffer[fd][0] = '\0';
	return (0);
}

static ssize_t	process_buffer(char buffer[MAX_FD][BUFFER_SIZE + 1], int fd,
		t_vector *line_vector)
{
	ssize_t	result;

	if (!buffer || !line_vector || fd < 0 || fd >= MAX_FD)
		return (-1);
	result = process_line_with_newline(buffer, fd, line_vector);
	if (result == 1)
		return (1);
	if (result == -1)
		return (-1);
	return (process_line_without_newline(buffer, fd, line_vector));
}

static ssize_t	fill_line(int fd, char buffer[MAX_FD][BUFFER_SIZE + 1],
		t_vector *line_vector)
{
	ssize_t	read_len;
	ssize_t	result;

	while (1)
	{
		if (buffer[fd][0] == '\0')
		{
			read_len = read(fd, buffer[fd], BUFFER_SIZE);
			if (read_len >= 0)
				buffer[fd][read_len] = '\0';
			if (read_len < 0)
				return (-1);
			if (read_len == 0)
				return (0);
		}
		result = process_buffer(buffer, fd, line_vector);
		if (result != 0)
			return (result);
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];
	t_vector	line_vector;
	ssize_t		result;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	init_vector(&line_vector, sizeof(char));
	result = fill_line(fd, buffer, &line_vector);
	if (result == -1 || (result == 0 && line_vector.size == 0))
	{
		free_vector(&line_vector);
		return (NULL);
	}
	if (add_vector(&line_vector, "\0", 1) == -1)
	{
		free_vector(&line_vector);
		return (NULL);
	}
	if (resize_vector(&line_vector) == -1)
	{
		free_vector(&line_vector);
		return (NULL);
	}
	return (line_vector.array);
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
//     int fd1;
// 	int fd2;
//     char *line1;
// 	char *line2;

//     fd1 = open("copy.txt", O_RDONLY);
//     fd2 = open("test.txt", O_RDONLY);
//     while (line1 != NULL || line2 != NULL)
//     {
//         if (line1 != NULL)
//         {
// 			line1 = get_next_line(fd1);
//             printf("copy.txt: %s", line1);
//             free(line1);
//         }
//         if (line2 != NULL)
//         {
// 			line2 = get_next_line(fd2);
//             printf("test.txt: %s", line2);
//             free(line2);
//         }
//     }
//     close(fd1);
//     close(fd2);
//     return (0);
// }