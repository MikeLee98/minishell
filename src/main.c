#include "minishell.h"

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
    t_env *env;
    char **array;
    t_env *tmp;
	int i;

	i = 0;
    env = init_env(envp);

	ft_env(env);
	// printf ("ola");
    // free_env_array(array);
	env_free_all(env);

    return (0);
}
