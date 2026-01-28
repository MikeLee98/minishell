/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:04:51 by migusant          #+#    #+#             */
/*   Updated: 2026/01/27 23:52:16 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pipeline_child_exec(t_pipeline *p)
{
	setup_signals(SIG_DEFAULT);
	signal(SIGPIPE, SIG_IGN);
	if (p->prev_fd != -1)
	{
		dup2(p->prev_fd, STDIN_FILENO);
		close(p->prev_fd);
	}
	if (p->current->next)
	{
		close(p->pipefd[0]);
		dup2(p->pipefd[1], STDOUT_FILENO);
		close(p->pipefd[1]);
	}
	if (apply_redirections(p->current) != 0)
		exit(1);
	if (is_builtin(p->current->args[0]))
		exit(run_builtin(p->current->args));
	execve_with_path(p->current);
	exit(127);
}

void	wait_all_pipeline(pid_t last_pid, t_pipeline *p)
{
	pid_t	wait_pid;
	int		last_status;

	last_status = 0;
	wait_pid = wait(&p->status);
	while (wait_pid > 0)
	{
		if (wait_pid == last_pid)
			last_status = p->status;
		wait_pid = wait(&p->status);
	}
	handle_child_status(last_status);
}
