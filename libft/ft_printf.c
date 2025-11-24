/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:05:40 by mario             #+#    #+#             */
/*   Updated: 2025/08/02 17:46:45 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sort_format(char c, va_list args)
{
	if (c == 'c')
		return (ft_printf_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_printf_putstr(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_printf_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_printf_putunsigned(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_printf_puthex(va_arg(args, unsigned int), 0));
	else if (c == 'X')
		return (ft_printf_puthex(va_arg(args, unsigned int), 1));
	else if (c == 'p')
		return (ft_printf_putptr(va_arg(args, void *)));
	else if (c == '%')
		return (ft_printf_putchar('%'));
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, format);
	i = -1;
	count = 0;
	if (!format || write(1, "", 0) == -1)
		return (-1);
	while (format[++i])
	{
		if (format[i] == '%' && format[i + 1])
			count += ft_sort_format(format[++i], args);
		else if (format[i] == '%')
			return (-1);
		else
			count += write(1, &format[i], 1);
	}
	va_end(args);
	return (count);
}
