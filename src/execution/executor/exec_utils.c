#include "../../../includes/minishell.h"

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "echo") == 0)
        return (1);
    if (ft_strcmp(cmd, "cd") == 0)
        return (1);
    if (ft_strcmp(cmd, "pwd") == 0)
        return (1);
    if (ft_strcmp(cmd, "export") == 0)
        return (1);
    if (ft_strcmp(cmd, "unset") == 0)
        return (1);
    if (ft_strcmp(cmd, "env") == 0)
        return (1);
    if (ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0);
}

int builtin_needs_parent(char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "cd") == 0)
        return (1);
    if (ft_strcmp(cmd, "export") == 0)
        return (1);
    if (ft_strcmp(cmd, "unset") == 0)
        return (1);
    if (ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0);
}

int run_builtin(t_shell *shell, char **args)
{
    if (ft_strcmp(args[0], "echo") == 0)
        return (ft_echo(args), 0);
    if (ft_strcmp(args[0], "cd") == 0)
        return (ft_cd(shell, args), 0);
    if (ft_strcmp(args[0], "pwd") == 0)
        return (ft_pwd(), 0);
    if (ft_strcmp(args[0], "export") == 0)
        return (ft_export(shell, args), 0);
    if (ft_strcmp(args[0], "unset") == 0)
        return (ft_unset(shell, args), 0);
    if (ft_strcmp(args[0], "env") == 0)
        return (ft_env(shell), 0);
    if (ft_strcmp(args[0], "exit") == 0)
        return (ft_exit(shell, args), shell->exit_code);
    return (1);
}

int has_slash(char *s)
{
    while (*s)
    {
        if (*s == '/')
            return (1);
        s++;
    }
    return (0);
}
