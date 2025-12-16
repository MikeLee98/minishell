#include "../../../includes/minishell.h"

int apply_redirections(t_cmd *cmd)
{
    t_redir *r;
    int     fd;

    r = cmd->redirections;
    while (r)
    {
        if (r->type == TOKEN_REDIR_IN)
            fd = open(r->file, O_RDONLY);
        else if (r->type == TOKEN_REDIR_OUT)
            fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (r->type == TOKEN_REDIR_APPEND)
            fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open_heredoc_fd(r);
        if (fd < 0)
            return (1);
        if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_REDIR_HEREDOC)
            dup2(fd, STDIN_FILENO);
        else
            dup2(fd, STDOUT_FILENO);
        close(fd);
        r = r->next;
    }
    return (0);
}
