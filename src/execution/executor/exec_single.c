#include "../../../includes/minishell.h"

static void save_fds(int saved[3])
{
    saved[0] = dup(STDIN_FILENO);
    saved[1] = dup(STDOUT_FILENO);
    saved[2] = dup(STDERR_FILENO);
}

static void restore_fds(int saved[3])
{
    dup2(saved[0], STDIN_FILENO);
    dup2(saved[1], STDOUT_FILENO);
    dup2(saved[2], STDERR_FILENO);

    close(saved[0]);
    close(saved[1]);
    close(saved[2]);
}

void execute_single(t_shell *shell, t_cmd *cmd)
{
    pid_t   pid;
    int     status;
	int saved_fds[3];

    if (!cmd || !cmd->args || !cmd->args[0])
        return;
    if (is_builtin(cmd->args[0]))
    {
		save_fds(saved_fds);
        if (apply_redirections(cmd) != 0)
        {
			restore_fds(saved_fds);
            shell->exit_code = 1;
            return;
        }
        shell->exit_code = run_builtin(shell, cmd->args);
		restore_fds(saved_fds);
        return;
    }
    pid = fork();
    if (pid == 0)
    {
		signal(SIGINT, SIG_DFL);
    	signal(SIGQUIT, SIG_DFL);
        if (apply_redirections(cmd) != 0)
            exit(1);
        execve_with_path(shell, cmd);
        exit(127);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        shell->exit_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->exit_code = 128 + WTERMSIG(status);
}
