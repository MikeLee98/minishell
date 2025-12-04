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

static void    free_env_array(char **array)
{
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

int main(int ac, char **av, char **envp)
{
    t_shell shell;

    shell.env = init_env(envp);
    shell.exit_status = 0;
    // minishell_loop(&shell);
	ft_env(&shell, NULL);
	ft_export(&shell.env, NULL);
	env_free_all(shell.env);

    return (0);
}
