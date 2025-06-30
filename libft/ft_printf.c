/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:08:36 by williamguer       #+#    #+#             */
/*   Updated: 2025/06/30 14:05:17 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_formatspercentage(va_list args, const char format)
{
	int	result;

	result = 0;
	if (format == 'c')
		result += ft_putchar(va_arg(args, int));
	else if (format == 's')
		result += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		result += prt_address(va_arg(args, size_t), false);
	else if (format == 'd' || format == 'i')
		result += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		result += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		result += prt_hexa(va_arg(args, size_t), false);
	else if (format == 'X')
		result += prt_hexa(va_arg(args, size_t), true);
	else if (format == '%')
		result += ft_putchar('%');
	else
	{
		ft_putchar(format);
		result += 2;
	}
	return (result);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		result;
	va_list	args;

	i = 0;
	result = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				return (-1);
			result += ft_formatspercentage(args, str[i + 1]);
			i++;
		}
		else
			result += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (result);
}
