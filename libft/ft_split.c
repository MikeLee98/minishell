/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:18:44 by mario             #+#    #+#             */
/*   Updated: 2025/10/30 02:48:02 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	size_t	count;
	size_t	x;

	count = 0;
	x = 0;
	while (*s)
	{
		if (*s != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (*s == c)
			x = 0;
		s++;
	}
	return (count);
}

static void	*ft_free(char **str_ptr, int count)
{
	while (count--)
		free(str_ptr[count]);
	free(str_ptr);
	return (NULL);
}

char	**ft_fill_split(const char *s, char c, char **str_ptr)
{
	size_t	i;
	size_t	j;
	int		wrd_srt_i;
	size_t	s_len;

	i = 0;
	j = 0;
	wrd_srt_i = -1;
	s_len = ft_strlen(s);
	while (i <= s_len)
	{
		if (s[i] != c && wrd_srt_i < 0)
			wrd_srt_i = i;
		else if ((s[i] == c || i == s_len) && wrd_srt_i >= 0)
		{
			str_ptr[j] = ft_substr(s, wrd_srt_i, i - wrd_srt_i);
			if (!(str_ptr[j]))
				return (ft_free(str_ptr, j));
			j++;
			wrd_srt_i = -1;
		}
		i++;
	}
	return (str_ptr);
}

char	**ft_split(const char *s, char c)
{
	char	**str_ptr;

	if (!s)
		return (NULL);
	str_ptr = ft_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	if (!str_ptr)
		return (NULL);
	return (ft_fill_split(s, c, str_ptr));
}
