/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:54:59 by mario             #+#    #+#             */
/*   Updated: 2026/02/10 17:01:23 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	executor(void)
{
	if (!shell()->cmds)
		return ;
	if (!shell()->cmds->next)
		execute_single(shell()->cmds);
	else
		execute_pipeline(shell()->cmds);
	close_unused_hd_fds(NULL);
}

int	run_builtin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args));
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(args));
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	return (1);
}

void	close_unused_hd_fds(t_cmd *current_cmd)
{
	t_cmd	*cmd;
	t_redir	*r;

	cmd = shell()->cmds;
	while (cmd)
	{
		if (current_cmd && cmd == current_cmd)
		{
			cmd = cmd->next;
			continue ;
		}
		r = cmd->redirections;
		while (r)
		{
			if (r->type == TOKEN_REDIR_HEREDOC && r->fd >= 0)
			{
				close(r->fd);
				r->fd = -1;
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}

void	close_previous_hd_fds(t_redir *redir_list, t_redir *current)
{
	t_redir	*r;

	r = redir_list;
	while (r && r != current)
	{
		if (r->type == TOKEN_REDIR_HEREDOC && r->fd >= 0)
		{
			close(r->fd);
			r->fd = -1;
		}
		r = r->next;
	}
}
