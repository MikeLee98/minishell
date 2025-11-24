/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:58:38 by mario             #+#    #+#             */
/*   Updated: 2025/08/02 17:47:04 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_putptr(void *ptr)
{
	if (!ptr)
		return (write(1, "(nil)", 5));
	return (write(1, "0x", 2) + ft_printf_puthex((unsigned long)ptr, 0));
}
