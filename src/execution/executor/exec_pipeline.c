/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:55:04 by mario             #+#    #+#             */
/*   Updated: 2026/01/22 19:36:12 by mario            ###   ########.fr       */
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

static void	pipeline_child_exec(t_pipeline *p)
{
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

void	execute_pipeline(t_cmd *cmd)
{
	t_pipeline	p;

	p.prev_fd = -1;
	p.current = cmd;
	while (p.current)
	{
		if (p.current->next && create_pipe_safe(p.pipefd))
			return ;
		if (!p.current->args || !p.current->args[0])
		{
			handle_empty_command_pipeline(p.current, p.pipefd);
			p.current = p.current->next;
			continue ;
		}
		p.pid = fork();
		if (p.pid == 0)
			pipeline_child_exec(&p);
		update_prev_fd(&p);
		p.current = p.current->next;
	}
	if (p.prev_fd != -1)
		close(p.prev_fd);
	while (wait(&p.status) > 0)
		handle_child_status(p.status);
}
