#include "../../../includes/minishell.h"

t_env   *env_find(t_env *env, char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return (env);
        env = env->next;
    }
    return (NULL);
}

char    *ft_getenv(t_env *env, char *key)
{
    t_env *node;

    node = env_find(env, key);
    if (node)
        return (node->value);
    return (NULL);
}

void free_env_array_nodes(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = tmp;
    }
}
