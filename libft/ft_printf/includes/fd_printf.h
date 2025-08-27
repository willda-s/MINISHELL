/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:01:24 by akarapkh          #+#    #+#             */
/*   Updated: 2025/06/28 14:23:46 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_PRINTF_H
# define FD_PRINTF_H

# include "../../vectors/includes/vectors.h"
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

ssize_t	ft_process_input(const char *input, va_list args, t_vector *buffer);
ssize_t	ft_process_format(const char *input, va_list args, t_vector *buffer);
ssize_t	ft_input_check(const char *input, va_list args, t_vector *buffer);
ssize_t	print_string(char *s, t_vector *buffer);
int		print_int(int n, t_vector *buffer);
int		print_char(char c, t_vector *buffer);
int		print_pointer(void *ptr, t_vector *buffer);
int		print_hex_upper(unsigned int num, t_vector *buffer);
int		print_hex_lower(unsigned int num, t_vector *buffer);
int		print_unsigned(unsigned int n, t_vector *buffer);
int		ft_dprintf(int fd, const char *input, ...);

#endif