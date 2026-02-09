/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:55:14 by mario             #+#    #+#             */
/*   Updated: 2026/02/09 20:52:43 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	set_underscore_to_last_arg(char **args)
{
	int	i;

	if (!args || !args[0])
		return ;
	i = 0;
	while (args[i])
		i++;
	if (i > 1)
		env_set(&shell()->env, "_", args[i - 1], 0);
	else
		env_set(&shell()->env, "_", args[0], 0);
}

static void	execute_builtin(t_cmd *cmd)
{
	int	saved_fds[3];
	int	ret;

	save_fds(saved_fds);
	if (apply_redirections(cmd) != 0)
	{
		restore_fds(saved_fds);
		shell()->exit_code = 1;
		return ;
	}
	env_set(&shell()->env, "_", cmd->args[0], 0);
	ret = run_builtin(cmd->args);
	if (shell()->should_exit)
	{
		cleanup_resources(CLEANUP_PARENT);
		restore_fds(saved_fds);
		exit(shell()->exit_code);
	}
	shell()->exit_code = ret;
	set_underscore_to_last_arg(cmd->args);
	restore_fds(saved_fds);
}

static void	execute_external(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		shell()->exit_code = 1;
		return ;
	}
	if (pid == 0)
	{
		setup_signals(SIG_DEFAULT);
		if (apply_redirections(cmd) != 0)
		{
			cleanup_resources(CLEANUP_CHILD);
			exit(1);
		}
		execve_with_path(cmd);
	}
	setup_signals(SIG_IGNORE);
	waitpid(pid, &status, 0);
	setup_signals(SIG_INTERACTIVE);
	handle_child_status(status);
	set_underscore_to_last_arg(cmd->args);
}

void	execute_single(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		if (cmd && cmd->redirections)
			shell()->exit_code = handle_redirections(cmd);
		return ;
	}
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd);
		return ;
	}
	execute_external(cmd);
}
