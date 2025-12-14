#include "../../../includes/minishell.h"

void executor(t_shell *shell)
{
    if (!shell->cmds || !shell->cmds->args || !shell->cmds->args[0])
        return;

    if (!shell->cmds->next)
        execute_simple(shell, shell->cmds);
    else
        execute_pipeline(shell, shell->cmds);
}


