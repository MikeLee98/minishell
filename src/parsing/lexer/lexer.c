/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:17:32 by migusant          #+#    #+#             */
/*   Updated: 2026/02/04 16:47:19 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_token	*create_operator_token(char *input, int *i)
{
	if (input[*i] == '|')
		return (create_token(TOKEN_PIPE, ft_strdup("|")));
	else if (input[*i] == ';')
		return (create_token(TOKEN_SEMICOLON, ft_strdup(";")));
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		(*i)++;
		return (create_token(TOKEN_REDIR_HEREDOC, ft_strdup("<<")));
	}
	else if (input[*i] == '<')
		return (create_token(TOKEN_REDIR_IN, ft_strdup("<")));
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		(*i)++;
		return (create_token(TOKEN_REDIR_APPEND, ft_strdup(">>")));
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '|')
			(*i)++;
		return (create_token(TOKEN_REDIR_OUT, ft_strdup(">")));
	}
	return (NULL);
}

static int	handle_operator(t_token **head, char *input, int *i)
{
	t_token	*new_token;

	new_token = create_operator_token(input, i);
	if (!new_token)
		return (0);
	add_token(head, new_token);
	return (1);
}

static int	handle_token(t_token **head, char *input, int *i)
{
	char	*word;
	t_token	*new_token;

	if (is_special_char(input[*i]))
	{
		if (!handle_operator(head, input, i))
			return (0);
		(*i)++;
	}
	else
	{
		word = handle_word(input, i);
		if (!word)
			return (0);
		new_token = create_token(TOKEN_WORD, word);
		if (!new_token)
			return (0);
		add_token(head, new_token);
	}
	return (1);
}

static void	handle_fd_prefix(char *input, int *i)
{
	while (input[*i] && is_fd_prefix(input[*i]))
	{
		if (input[*i + 1] && is_redir_char(input[*i + 1]))
		{
			if ((input[*i] == '2' && input[*i + 1] == '>')
				|| (input[*i] == '&' && input[*i + 1] == '>'))
				shell()->stderr_redir = 1;
			(*i)++;
		}
		else
			break ;
	}
}

t_token	*lexer(char *input)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	shell()->stderr_redir = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		handle_fd_prefix(input, &i);
		if (!handle_token(&head, input, &i))
		{
			free_tokens(head);
			return (NULL);
		}
	}
	return (head);
}
