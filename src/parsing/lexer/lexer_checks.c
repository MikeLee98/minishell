/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:50:08 by migusant          #+#    #+#             */
/*   Updated: 2026/02/04 16:50:38 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	is_special_char(char c)
{
	return (c == '|' || c == ';' || c == '<' || c == '>');
}

int	is_redir_char(char c)
{
	return (c == '>' || c == '<');
}

int	is_fd_prefix(char c)
{
	return (ft_isdigit(c) || c == '&');
}
