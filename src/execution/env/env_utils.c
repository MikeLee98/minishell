#include "../../../includes/minishell.h"

t_env   *env_find(t_env *env, char *key)
{
    while (env)
    {
        if (ft_strncmp(env->key, key, ft_strlen(env->key) + 1) == 0)
            return (env);
        env = env->next;
    }
    return (NULL);
}

char    *env_get_value(t_env *env, char *key)
{
    t_env *node;

    node = env_find(env, key);
    if (node)
        return (node->value);
    return (NULL);
}
