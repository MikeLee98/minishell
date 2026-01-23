/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 09:54:52 by migusant          #+#    #+#             */
/*   Updated: 2026/01/23 19:53:50 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*handle_expansion_char(char *str, int *i,
	char **result)
{
	char	*expansion;

	if (str[*i] == '\\' && str[*i + 1] && (str[*i + 1] == '$'
			|| str[*i + 1] == '"' || str[*i + 1] == '\\'))
	{
		*result = append_char(*result, str[*i + 1]);
		(*i) += 2;
	}
	else if (str[*i] == '$')
	{
		expansion = expand_variable(str, i);
		*result = append_string(*result, expansion, 1);
	}
	else
	{
		*result = append_char(*result, str[*i]);
		(*i)++;
	}
	return (*result);
}

char	*expand_single_quotes(char *str, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*expand_double_quotes(char *str, int *i)
{
	char	*result;

	(*i)++;
	result = ft_strdup("\"");
	if (!result)
		return (NULL);
	while (str[*i] && str[*i] != '"')
	{
		if (!handle_expansion_char(str, i, &result))
			return (NULL);
	}
	if (str[*i] == '"')
	{
		result = append_char(result, '"');
		if (!result)
			return (NULL);
		(*i)++;
	}
	return (result);
}

char	*expand_ansi_c_quotes(char *str, int *i)
{
	int	start;

	(*i) += 2;
	start = *i;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	return (ft_substr(str, start, *i - start - 1));
}
