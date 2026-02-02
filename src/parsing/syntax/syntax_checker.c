/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 09:42:51 by migusant          #+#    #+#             */
/*   Updated: 2026/02/02 15:03:11 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_redir_syntax(t_token *token)
{
	if (!token->next)
	{
		print_syntax_error(NULL);
		return (0);
	}
	else if (token->next->type == TOKEN_PIPE)
	{
		print_syntax_error(token->next);
		return (0);
	}
	else if (is_redir_token(token->next->type))
	{
		print_syntax_error(token->next);
		return (0);
	}
	else if (token->next->type != TOKEN_WORD)
	{
		print_syntax_error(token->next);
		return (0);
	}
	return (1);
}

static int	check_pipe_syntax(t_token *token, t_token *prev)
{
	if (!prev)
	{
		print_syntax_error(token);
		return (0);
	}
	else if (!token->next)
	{
		print_syntax_error(NULL);
		return (0);
	}
	else if (token->next->type == TOKEN_PIPE)
	{
		print_syntax_error(token->next);
		return (0);
	}
	return (1);
}

int	check_syntax(void)
{
	t_token	*current;
	t_token	*prev;

	if (!shell() || !shell()->toks)
		return (0);
	current = shell()->toks;
	prev = NULL;
	while (current)
	{
		if (is_redir_token(current->type))
		{
			if (!check_redir_syntax(current))
				return (shell()->exit_code = 2, 0);
		}
		else if (current->type == TOKEN_PIPE)
		{
			if (!check_pipe_syntax(current, prev))
				return (shell()->exit_code = 2, 0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}
