/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:55:17 by marioro2          #+#    #+#             */
/*   Updated: 2025/04/23 19:57:24 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	i = nmemb * size;
	if (i / nmemb != size)
		return (NULL);
	ptr = malloc(i);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, i);
	return (ptr);
}
