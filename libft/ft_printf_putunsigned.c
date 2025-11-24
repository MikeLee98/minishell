/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putunsigned.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:56:11 by mario             #+#    #+#             */
/*   Updated: 2025/08/02 17:46:57 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_putunsigned(unsigned int n)
{
	long	nb;
	char	c;

	nb = n;
	if (nb >= 10)
		return (ft_printf_putnbr(nb / 10) + ft_printf_putnbr(nb % 10));
	c = nb + '0';
	return (write(1, &c, 1));
}
