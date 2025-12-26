#include "../../../includes/minishell.h"

static int create_heredoc(char *delimiter)
{
    int     pipefd[2];
    pid_t   pid;
    int     status;
    char    *line;

    if (pipe(pipefd) == -1)
        return (-1);

    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_IGN);

        close(pipefd[0]);

        while (1)
        {
            line = readline("> ");
            if (!line || ft_strcmp(line, delimiter) == 0)
            {
                free(line);
                break;
            }
			if (flag_hdoc == 1)
				expand
			else
            	write(pipefd[1], line, ft_strlen(line));
            write(pipefd[1], "\n", 1);
            free(line);
        }
        close(pipefd[1]);
        exit(0);
    }

    close(pipefd[1]);
    waitpid(pid, &status, 0);

    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        close(pipefd[0]);
        return (-1);
    }
    return (pipefd[0]);
}

int prepare_heredocs(t_cmd *cmds)
{
    t_cmd   *cmd;
    t_redir *r;

    cmd = cmds;
    while (cmd)
    {
        r = cmd->redirections;
        while (r)
        {
            if (r->type == TOKEN_REDIR_HEREDOC)
            {
                r->fd = create_heredoc(r->file);
                if (r->fd < 0)
                    return (-1);
            }
            r = r->next;
        }
        cmd = cmd->next;
    }
    return (0);
}
