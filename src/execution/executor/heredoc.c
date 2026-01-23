/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 heredoc.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: mario <mario@student.42.fr>				+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/01/21 19:55:26 by mario			   #+#	  #+#			  */
/*	 Updated: 2026/01/21 19:55:27 by mario			  ###	########.fr		  */
/*																			  */
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

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(hd_expand, write_fd, line);
		free(line);
	}
	close(write_fd);
	exit(0);
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
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		return (-1);
	}
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
