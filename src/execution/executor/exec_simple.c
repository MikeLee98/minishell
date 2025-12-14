#include "../../../includes/minishell.h"

// void execute_single(t_shell *shell, t_cmd *cmd)
// {
//     if (is_builtin(cmd->args[0]) && builtin_needs_parent(cmd->args[0]))
//     {
//         apply_redirections(cmd);
//         shell->exit_code = run_builtin(shell, cmd->args);
//         return;
//     }

//     pid = fork();
//     if (pid == 0)
//     {
//         apply_redirections(cmd);
//         if (is_builtin(cmd->args[0]))
//             exit(run_builtin(shell, cmd->args));
//         execve_with_path(shell, cmd);
//         exit(126 or 127);
//     }
//     waitpid(pid, &status, 0);
//     update_exit_code(shell, status);
// }
