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

	if (ac != 2)
		return (0);
    shell.env = init_env(envp);
    shell.exit_status = 0;
	if (ft_strncmp(av[1], "env", 3))
		ft_env(&shell, NULL);
	if (ft_strncmp(av[1], "export", 6))
		ft_export(&shell.env, NULL);
	env_free_all(shell.env);

    return (0);
}
