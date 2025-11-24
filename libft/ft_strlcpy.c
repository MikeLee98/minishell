/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 02:51:07 by marioro2          #+#    #+#             */
/*   Updated: 2025/10/30 02:49:21 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	if (!dst || !src)
		return (0);
	src_len = ft_strlen(src);
	if (size > 0)
	{
		if (src_len + 1 < size)
			ft_memcpy(dst, src, src_len + 1);
		else
			ft_memcpy(dst, src, size - 1);
		dst[size - 1] = 0;
	}
	return (src_len);
}
