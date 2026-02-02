/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_mark.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:17:15 by migusant          #+#    #+#             */
/*   Updated: 2026/02/02 15:17:35 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
