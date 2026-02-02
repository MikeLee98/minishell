/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:01:27 by migusant          #+#    #+#             */
/*   Updated: 2026/02/02 15:04:15 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

void	print_syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!token)
		ft_putstr_fd("newline", 2);
	else if (token->type == TOKEN_PIPE)
		ft_putstr_fd("|", 2);
	else if (token->type == TOKEN_REDIR_IN)
		ft_putstr_fd("<", 2);
	else if (token->type == TOKEN_REDIR_OUT)
		ft_putstr_fd(">", 2);
	else if (token->type == TOKEN_REDIR_APPEND)
		ft_putstr_fd(">>", 2);
	else if (token->type == TOKEN_REDIR_HEREDOC)
		ft_putstr_fd("<<", 2);
	ft_putstr_fd("'\n", 2);
}
