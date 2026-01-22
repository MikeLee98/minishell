/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 exec_single.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: mario <mario@student.42.fr>				+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/01/21 19:55:14 by mario			   #+#	  #+#			  */
/*	 Updated: 2026/01/21 19:55:15 by mario			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_redirections(t_cmd *cmd)
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
	ret = run_builtin(cmd->args);
	if (shell()->should_exit)
	{
		cleanup_shell();
		restore_fds(saved_fds);
		exit(shell()->exit_code);
	}
	shell()->exit_code = ret;
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (apply_redirections(cmd) != 0)
			exit(1);
		execve_with_path(cmd);
		exit(127);
	}
	waitpid(pid, &status, 0);
	setup_signals();
	handle_child_status(status);
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
