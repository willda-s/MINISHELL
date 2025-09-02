/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 07:34:41 by akarapkh          #+#    #+#             */
/*   Updated: 2025/09/02 16:20:05 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

int	ft_dprintf(int fd, const char *input, ...)
{
	va_list		args;
	t_vector	buffer;
	ssize_t		write_result;
	ssize_t		total_printed;

	if (!input)
		return (-1);
	init_vector(&buffer, sizeof(char));
	va_start(args, input);
	total_printed = ft_process_input(input, args, &buffer);
	va_end(args);
	if (total_printed == -1)
	{
		free_vector(&buffer);
		return (-1);
	}
	write_result = write(fd, buffer.array, buffer.size);
	free_vector(&buffer);
	if (write_result == -1)
		return (-1);
	return (total_printed);
}
