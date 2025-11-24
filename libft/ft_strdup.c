/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:13:42 by marioro2          #+#    #+#             */
/*   Updated: 2025/04/23 20:09:56 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) + 1;
	copy = malloc(len);
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, s, len);
	return (copy);
}
