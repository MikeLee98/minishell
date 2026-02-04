/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:55:09 by mario             #+#    #+#             */
/*   Updated: 2026/02/04 13:10:37 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	redir_error(char *file)
{
	if (!shell()->stderr_redir)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	return (-1);
}

static int	open_redir_fd(t_redir *r)
{
	if (r->type == TOKEN_REDIR_HEREDOC)
		return (r->fd);
	if (r->type == TOKEN_REDIR_IN)
		return (open(r->file, O_RDONLY));
	if (r->type == TOKEN_REDIR_OUT)
		return (open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	if (r->type == TOKEN_REDIR_APPEND)
		return (open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0666));
	return (-1);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirections;
	while (r)
	{
		fd = open_redir_fd(r);
		if (fd < 0)
			return (redir_error(r->file));
		if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_REDIR_HEREDOC)
		{
			if (dup2(fd, STDIN_FILENO) < 0)
				return (close(fd), -1);
		}
		else if (dup2(fd, STDOUT_FILENO) < 0)
			return (close(fd), -1);
		close(fd);
		if (r->type == TOKEN_REDIR_HEREDOC)
			r->fd = -1;
		r = r->next;
	}
	return (0);
}
