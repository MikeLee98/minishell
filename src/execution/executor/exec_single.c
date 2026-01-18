#include "../../../includes/minishell.h"

void execute_single(t_cmd *cmd)
{
	int		saved_fds[3];
	pid_t	pid;
	int		status;

	if (!cmd)
		return ;
	if (!cmd->args || !cmd->args[0])
	{
		if (cmd->redirections)
		{
			save_fds(saved_fds);
			if (apply_redirections(cmd) != 0)
				shell()->exit_code = 1;
			else
				shell()->exit_code = 0;
			restore_fds(saved_fds);
		}
		return ;
	}
	if (is_builtin(cmd->args[0]))
	{
		save_fds(saved_fds);
		if (apply_redirections(cmd) != 0)
		{
			restore_fds(saved_fds);
			shell()->exit_code = 1;
			return ;
		}
		shell()->exit_code = run_builtin(cmd->args);
		restore_fds(saved_fds);
		return ;
	}
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status))
		shell()->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell()->exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
	}
}
