/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:11:08 by migusant          #+#    #+#             */
/*   Updated: 2026/01/31 00:21:28 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*extract_var_name(char *str, int *i)
{
	int	start;

	(*i)++;
	if (str[*i] == '?')
		return (dup_char_and_advance('?', i));
	if (ft_isdigit(str[*i]))
		return (dup_char_and_advance(str[*i], i));
	if (str[*i] && !ft_isalnum(str[*i]) && str[*i] != '_')
		return (dup_char_and_advance(str[*i], i));
	start = *i;
	if (str[*i] && (ft_isalpha(str[*i]) || str[*i] == '_'))
	{
		(*i)++;
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

char	*expand_variable(char *str, int *i)
{
	if (str[*i] == '\\' && str[*i + 1])
	{
		(*i)++;
		return (dup_char_and_advance(str[*i], i));
	}
	else if (str[*i] == '$')
	{
		if (str[*i + 1] && (ft_isalnum(str[*i + 1])
				|| str[*i + 1] == '_' || str[*i + 1] == '?'))
			return (expand_var_from_name(extract_var_name(str, i)));
		else
			return (dup_char_and_advance('$', i));
	}
	else
		return (dup_char_and_advance(str[*i], i));
}
