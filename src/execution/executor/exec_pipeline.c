#include "../../../includes/minishell.h"

void execute_pipeline(t_shell *shell, t_cmd *cmd)
{
    int pipefd[2];
    int prev_fd;
    pid_t pid;
    int status;
    t_cmd *current;

    prev_fd = -1;
    current = cmd;
    while (current)
    {
        if (current->next)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                return;
            }
        }
        pid = fork();
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (current->next)
            {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            if (apply_redirections(current) != 0)
                exit(1);
            if (is_builtin(current->args[0]))
                exit(run_builtin(shell, current->args));
            execve_with_path(shell, current);
            exit(127);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (current->next)
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
        current = current->next;
    }
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            shell->exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            shell->exit_code = 128 + WTERMSIG(status);
    }
}
