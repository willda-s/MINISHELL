/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:48:26 by willda-s          #+#    #+#             */
/*   Updated: 2025/04/25 19:11:23 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_bytes(ssize_t bytes, char *str)
{
	if (str != NULL && bytes != -1)
		return (str);
	if (errno != 0)
		errno = 1;
	return (free(str), NULL);
}

void	*set_errno(void)
{
	errno = 1;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*str;
	ssize_t		bytes;

	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (!buf[0])
		{
			bytes = read(fd, buf, BUFFER_SIZE);
			if (bytes <= 0)
				return (check_bytes(bytes, str));
			buf[bytes] = '\0';
		}
		str = ft_strjjoin(str, buf);
		if (!str)
			return (set_errno());
		if (str && ft_strcchr(buf, '\n') != -1)
			return (ft_strccpy(buf, buf + ft_strcchr(buf, '\n')), str);
		buf[0] = '\0';
		if (str == NULL)
			return (NULL);
	}
}
