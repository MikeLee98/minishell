/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 01:07:25 by mario             #+#    #+#             */
/*   Updated: 2025/10/30 02:51:13 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_putnbr(int n)
{
	int		count;
	long	nb;

	count = 0;
	nb = n;
	if (nb < 0)
	{
		count += ft_printf_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		count += ft_printf_putnbr(nb / 10);
		count += ft_printf_putnbr(nb % 10);
	}
	else
		count += ft_printf_putchar(nb + '0');
	return (count);
}
