#include "../../../includes/minishell.h"

void execute_single(t_shell *shell, t_cmd *cmd)
{
    pid_t  pid;
    int    status;

    if (is_builtin(cmd->args[0]) && builtin_needs_parent(cmd->args[0]))
    {
        apply_redirections(cmd);
        shell->exit_code = run_builtin(shell, cmd->args);
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        apply_redirections(cmd);

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
