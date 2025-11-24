/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 04:07:10 by marioro2          #+#    #+#             */
/*   Updated: 2025/10/30 02:48:39 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*tmp_dst;
	const unsigned char	*tmp_src;

	if (!dst && !src && n > 0)
		return (NULL);
	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	if (tmp_dst > tmp_src)
		while (n--)
			tmp_dst[n] = tmp_src[n];
	else
		ft_memcpy(tmp_dst, tmp_src, n);
	return (dst);
}
