#include "../../../includes/minishell.h"

void execute_pipeline(t_cmd *cmd)
{
    int     pipefd[2];
    int     prev_fd;
    t_cmd   *current;
    pid_t   pid;
    int     status;

    prev_fd = -1;
    current = cmd;
    while (current)
    {
        if (current->next && pipe(pipefd) == -1)
        {
            ft_putstr_fd("minishell: pipe: ", 2);
            ft_putstr_fd(strerror(errno), 2);
            ft_putstr_fd("\n", 2);
            return;
        }
        if (!current->args || !current->args[0])
        {
            if (current->redirections)
            {
                int saved_fds[3];
                save_fds(saved_fds);
                if (apply_redirections(current) != 0)
                    shell()->exit_code = 1;
                else
                    shell()->exit_code = 0;
                restore_fds(saved_fds);
            }
            if (current->next)
            {
                close(pipefd[1]);
                prev_fd = pipefd[0];
            }
            current = current->next;
            continue;
        }
        pid = fork();
        if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
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
                exit(run_builtin(current->args));
            execve_with_path(current);
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
    if (prev_fd != -1)
        close(prev_fd);
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            shell()->exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            shell()->exit_code = 128 + WTERMSIG(status);
    }
}
