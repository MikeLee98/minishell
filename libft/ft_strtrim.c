/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:20:47 by mario             #+#    #+#             */
/*   Updated: 2025/04/29 18:09:46 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (ft_substr(s1, start, end - start));
}

// int	main()
// {
// char * trim = ft_strtrim("   xxxkawabanga", " x");
//     printf("diff: %d\n", strcmp(trim, "kawabanga"));
//     free(trim);
//     trim = ft_strtrim("kawabanga    xxx", " x");
//     printf("diff: %d\n", strcmp(trim, "kawabanga"));
//     free(trim);
//     trim = ft_strtrim("   xxxkawabanga    xxx", " x");
//     printf("diff: %d\n", strcmp(trim, "kawabanga"));
//     free(trim);
//     trim = ft_strtrim("   xxx    xxx", " x");
//     printf("diff: %d\n", strcmp(trim, ""));
//     free(trim);
//     trim = ft_strtrim("123456", "");
//     printf("diff: %d\n", strcmp(trim, "123456"));
//     free(trim);
//     trim = ft_strtrim("", "123456");
//     printf("diff: %d\n", strcmp(trim, ""));
//     free(trim);
//     trim = ft_strtrim("", "");
//     printf("diff: %d\n", strcmp(trim, ""));
//     free(trim);
//     trim = ft_strtrim("abcdba", "acb");
//     printf("diff: %d\n", strcmp(trim, "d"));
//     free(trim);
//     trim = ft_strtrim(NULL, NULL);
//     printf("nil: %p\n", trim);
//     free(trim);
// }
