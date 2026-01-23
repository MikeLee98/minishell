/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 09:57:13 by migusant          #+#    #+#             */
/*   Updated: 2026/01/23 19:56:09 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	skip_quotes(char *str, int *i, char quote_char)
{
	int	len;

	(*i)++;
	len = 0;
	while (str[*i] && str[*i] != quote_char)
	{
		len++;
		(*i)++;
	}
	if (str[*i] == quote_char)
		(*i)++;
	return (len);
}

int	count_unquoted_len(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			len += skip_quotes(str, &i, '\'');
		else if (str[i] == '"')
			len += skip_quotes(str, &i, '"');
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	copy_single_quoted(char *dest, char *src, int *j, int *i)
{
	(*i)++;
	while (src[*i] && src[*i] != '\'')
		dest[(*j)++] = src[(*i)++];
	if (src[*i] == '\'')
		(*i)++;
}

static void	copy_double_quoted(char *dest, char *src, int *j, int *i)
{
	(*i)++;
	while (src[*i] && src[*i] != '"')
		dest[(*j)++] = src[(*i)++];
	if (src[*i] == '"')
		(*i)++;
}

void	copy_unquoted(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\'')
			copy_single_quoted(dest, src, &j, &i);
		else if (src[i] == '"')
			copy_double_quoted(dest, src, &j, &i);
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
}
