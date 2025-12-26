#include "../../../includes/minishell.h"

void execute_single(t_shell *shell, t_cmd *cmd)
{
    pid_t   pid;
    int     status;

    if (!cmd || !cmd->args || !cmd->args[0])
        return;
    if (is_builtin(cmd->args[0]) && builtin_needs_parent(cmd->args[0]))
    {
        if (apply_redirections(cmd) != 0)
        {
            shell->exit_code = 1;
            return;
        }
        shell->exit_code = run_builtin(shell, cmd->args);
        return;
    }
    pid = fork();
    if (pid == 0)
    {
		signal(SIGINT, SIG_DFL);
    	signal(SIGQUIT, SIG_DFL);
        if (apply_redirections(cmd) != 0)
            exit(1);
        if (is_builtin(cmd->args[0]))
            exit(run_builtin(shell, cmd->args));
        execve_with_path(shell, cmd);
        exit(127);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        shell->exit_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->exit_code = 128 + WTERMSIG(status);
}
