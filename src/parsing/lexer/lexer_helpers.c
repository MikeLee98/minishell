/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 09:29:52 by migusant          #+#    #+#             */
/*   Updated: 2026/02/02 16:10:47 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	token->type = type;
	token->value = value;
	token->hd_expand = 0;
	token->wd_split = 0;
	token->next = NULL;
	return (token);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_fd_prefix(char c)
{
	return (ft_isdigit(c) || c == '&');
}

int	is_redir_char(char c)
{
	return (c == '>' || c == '<');
}
