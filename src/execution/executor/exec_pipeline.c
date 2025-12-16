#include "../../../includes/minishell.h"

void execute_pipeline(t_shell *shell, t_cmd *cmd)
{
    int     pipefd[2];
    int     prev_fd;
    pid_t   pid;
    int     status;

    prev_fd = -1;
    while (cmd)
    {
        if (cmd->next && pipe(pipefd) == -1)
            return;
        pid = fork();
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cmd->next)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }
            apply_redirections(cmd);
            if (is_builtin(cmd->args[0]))
                exit(run_builtin(shell, cmd->args));
            execve_with_path(shell, cmd);
            exit(127);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (cmd->next)
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
        cmd = cmd->next;
    }
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            shell->exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            shell->exit_code = 128 + WTERMSIG(status);
    }
}
