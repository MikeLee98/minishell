/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:55:26 by mario             #+#    #+#             */
/*   Updated: 2026/01/27 23:52:55 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	write_heredoc_line(int hd_expand, int fd, char *line)
{
	char	*expanded;

	if (hd_expand)
	{
		expanded = expand_token(line);
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static void	heredoc_child(int hd_expand, char *delimiter, int write_fd)
{
	char	*line;

	setup_signals(SIG_HEREDOC);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(write_fd);
			exit(1);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			close(write_fd);
			exit(0);
		}
		write_heredoc_line(hd_expand, write_fd, line);
		free(line);
	}
}

static void	print_heredoc_warning(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line N ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

static int	create_heredoc(int hd_expand, char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_child(hd_expand, delimiter, pipefd[1]);
	}
	close(pipefd[1]);
	setup_signals(SIG_IGNORE);
	waitpid(pid, &status, 0);
	setup_signals(SIG_INTERACTIVE);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(pipefd[0]);
		return (shell()->exit_code = 130, -1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		print_heredoc_warning(delimiter);
	return (pipefd[0]);
}

int	prepare_heredocs(void)
{
	t_cmd	*cmd;
	t_redir	*r;

	cmd = shell()->cmds;
	while (cmd)
	{
		r = cmd->redirections;
		while (r)
		{
			if (r->type == TOKEN_REDIR_HEREDOC)
			{
				r->fd = create_heredoc(r->hd_expand, r->file);
				if (r->fd < 0)
					return (-1);
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
