/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:55:20 by mario             #+#    #+#             */
/*   Updated: 2026/01/27 23:12:24 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	save_fds(int saved[3])
{
	saved[0] = dup(STDIN_FILENO);
	saved[1] = dup(STDOUT_FILENO);
	saved[2] = dup(STDERR_FILENO);
}

void	restore_fds(int saved[3])
{
	dup2(saved[0], STDIN_FILENO);
	dup2(saved[1], STDOUT_FILENO);
	dup2(saved[2], STDERR_FILENO);
	close(saved[0]);
	close(saved[1]);
	close(saved[2]);
}

void	handle_child_status(int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			shell()->exit_code = 130;
		else if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			shell()->exit_code = 131;
		}
		else
			shell()->exit_code = 128 + sig;
	}
	else if (WIFEXITED(status))
		shell()->exit_code = WEXITSTATUS(status);
}

int	handle_redirections(t_cmd *cmd)
{
	int	saved_fds[3];

	save_fds(saved_fds);
	if (apply_redirections(cmd) != 0)
	{
		restore_fds(saved_fds);
		return (1);
	}
	restore_fds(saved_fds);
	return (0);
}
