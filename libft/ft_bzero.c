/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:50:19 by marioro2          #+#    #+#             */
/*   Updated: 2025/04/24 14:08:22 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = (unsigned char *)ptr;
	while (n--)
		*(tmp_ptr++) = '\0';
}

// int	main()
// {
// 	char	s[] = "hello world";
// 	ft_bzero(s, 5);
// }
