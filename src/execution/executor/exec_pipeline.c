/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:55:04 by mario             #+#    #+#             */
/*   Updated: 2026/01/27 23:51:55 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	update_prev_fd(t_pipeline *p)
{
	if (p->prev_fd != -1)
		close(p->prev_fd);
	if (p->current->next)
	{
		close(p->pipefd[1]);
		p->prev_fd = p->pipefd[0];
	}
	else
		p->prev_fd = -1;
}

static void	handle_empty_command_pipeline(t_cmd *current, int pipefd[2])
{
	if (current->redirections)
		shell()->exit_code = handle_redirections(current);
	if (current->next)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

static int	create_pipe_safe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("minishell: pipe: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

static void	exec_pipeline_loop(t_pipeline *p, pid_t *last_pid)
{
	while (p->current)
	{
		if (p->current->next && create_pipe_safe(p->pipefd))
			return ;
		if (!p->current->args || !p->current->args[0])
		{
			handle_empty_command_pipeline(p->current, p->pipefd);
			p->current = p->current->next;
			continue ;
		}
		p->pid = fork();
		if (p->pid == 0)
			pipeline_child_exec(p);
		*last_pid = p->pid;
		update_prev_fd(p);
		p->current = p->current->next;
	}
}

void	execute_pipeline(t_cmd *cmd)
{
	t_pipeline	p;
	pid_t		last_pid;

	p.prev_fd = -1;
	p.current = cmd;
	last_pid = -1;
	exec_pipeline_loop(&p, &last_pid);
	if (p.prev_fd != -1)
		close(p.prev_fd);
	setup_signals(SIG_IGNORE);
	wait_all_pipeline(last_pid, &p);
	setup_signals(SIG_INTERACTIVE);
}
