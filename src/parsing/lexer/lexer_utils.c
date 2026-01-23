/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:18:02 by migusant          #+#    #+#             */
/*   Updated: 2026/01/23 19:50:10 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	calculate_quoted_length(char *input, int *i, char quote)
{
	int	len;

	len = 1;
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		len++;
		(*i)++;
	}
	if (input[*i] == quote)
	{
		len++;
		(*i)++;
	}
	return (len);
}

static int	calculate_word_length(char *input, int start)
{
	int	len;
	int	i;

	len = 0;
	i = start;
	while (input[i] && !is_whitespace(input[i])
		&& !is_special_char(input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
			len += calculate_quoted_length(input, &i, input[i]);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	copy_quoted_section(char *dst, char *src, int *dst_pos,
	int *src_pos)
{
	char	quote;

	quote = src[*src_pos];
	dst[*dst_pos] = quote;
	(*src_pos)++;
	(*dst_pos)++;
	while (src[*src_pos] && src[*src_pos] != quote)
	{
		dst[*dst_pos] = src[*src_pos];
		(*src_pos)++;
		(*dst_pos)++;
	}
	if (src[*src_pos] == quote)
	{
		dst[*dst_pos] = quote;
		(*src_pos)++;
		(*dst_pos)++;
	}
}

char	*handle_word(char *input, int *i)
{
	char	*word;
	int		len;
	int		j;

	len = calculate_word_length(input, *i);
	if (len == 0)
		return (NULL);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_char(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
			copy_quoted_section(word, input, &j, i);
		else
			word[j++] = input[(*i)++];
	}
	word[j] = '\0';
	return (word);
}
