/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:13:25 by migusant          #+#    #+#             */
/*   Updated: 2026/02/01 18:51:58 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_variable_assignment(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (str[i] == '=' && i > 0);
}

static int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static int	has_unquoted_whitespace(char *str)
{
	int		i;
	int		in_quote;
	char	quote_type;

	i = 0;
	in_quote = 0;
	quote_type = 0;
	while (str[i])
	{
		if (!in_quote && (str[i] == '"' || str[i] == '\''))
		{
			in_quote = 1;
			quote_type = str[i];
		}
		else if (in_quote && str[i] == quote_type)
		{
			in_quote = 0;
			quote_type = 0;
		}
		else if (!in_quote && (str[i] == ' ' || str[i] == '\t'))
			return (1);
		i++;
	}
	return (0);
}

void	mark_word_split(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD
			&& !is_variable_assignment(tokens->value)
			&& has_unquoted_whitespace(tokens->value))
			tokens->wd_split = 1;
		else
			tokens->wd_split = 0;
		tokens = tokens->next;
	}
}

void	mark_heredoc_expansion(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_REDIR_HEREDOC
			&& tokens->next
			&& tokens->next->type == TOKEN_WORD)
		{
			if (has_quotes(tokens->next->value))
				tokens->next->hd_expand = 0;
			else
				tokens->next->hd_expand = 1;
		}
		tokens = tokens->next;
	}
}
