/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_puthex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:56:54 by mario             #+#    #+#             */
/*   Updated: 2025/10/30 02:47:25 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_puthex(unsigned long n, int upper)
{
	char	*base;
	char	c;

	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		return (ft_printf_puthex(n / 16, upper)
			+ ft_printf_puthex(n % 16, upper));
	c = base[n % 16];
	return (write(1, &c, 1));
}
