/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:54:05 by marioro2          #+#    #+#             */
/*   Updated: 2025/10/30 02:54:55 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (src_len + size);
	if (src_len < size - dst_len)
		ft_memcpy(dst + dst_len, src, src_len + 1);
	else
		ft_memcpy(dst + dst_len, src, size - dst_len - 1);
	dst[size - 1] = 0;
	return (dst_len + src_len);
}
