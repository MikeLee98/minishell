#include "../../includes/minishell.h"

static void    env_free_node(t_env *node)
{
    if (!node)
        return;
    free(node->key);
    free(node->value);
    free(node);
}

static void    env_free_all(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env->next;
        env_free_node(env);
        env = tmp;
    }
}

int main(int ac, char **av, char **envp)
{
    t_shell shell;

	shell.exit_code = 0;
	if (ac < 2)
		return (0);

    shell.env = init_env(envp);

	if (!ft_strcmp(av[1], "env"))
		ft_env(&shell);

	if (!ft_strcmp(av[1], "export"))
	{
		ft_export(&shell, av);
		if (ac > 2)
			ft_env(&shell);
	}
	if (!ft_strcmp(av[1], "unset"))
	{
		ft_unset(&shell, av);
		ft_env(&shell);
	}
	if (!ft_strcmp(av[1], "cd"))
	{
		ft_cd(&shell, av);
		ft_env(&shell);
	}
	if (!ft_strcmp(av[1], "pwd"))
	{
		ft_pwd();
	}
	if (!ft_strcmp(av[1], "echo"))
	{
		ft_echo(av);
	}

	env_free_all(shell.env);
    return (0);
}
