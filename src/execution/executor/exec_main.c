#include "../../../includes/minishell.h"

void executor(t_shell *shell)
{
    if (!shell->cmds)
        return;

    if (!shell->cmds->next)
        execute_single(shell, shell->cmds);
    else
        execute_pipeline(shell, shell->cmds);
}

void execve_with_path(t_shell *shell, t_cmd *cmd)
{
    char    **paths;
    char    *full_path;
    char    *path_env;
    char    **envp;
    int     i;

    envp = env_to_array(shell->env);
    if (has_slash(cmd->args[0]))
    {
        execve(cmd->args[0], cmd->args, envp);
        perror(cmd->args[0]);
        exit(errno == EACCES ? 126 : 127);
    }
    path_env = ft_getenv(shell->env, "PATH");
    if (!path_env)
    {
        execve(cmd->args[0], cmd->args, envp);
        perror(cmd->args[0]);
        exit(127);
    }
    paths = ft_split(path_env, ':');
    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin3(paths[i], "/", cmd->args[0]);
        execve(full_path, cmd->args, envp);
        free(full_path);
        i++;
    }
    ft_printf("minishell: %s: command not found\n", cmd->args[0]);
    exit(127);
}
