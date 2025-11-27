#include "../minishell.h"

static int env_update(t_env *env, char *key, char *new_value)
{
    t_env *node;

    node = env_find(env, key);
    if (!node)
        return (0);
    free(node->value);
    node->value = ft_strdup(new_value);
    return (1);
}

static void    env_add_var(t_env **env, char *key, char *value)
{
    t_env   *new;

    new = malloc(sizeof(t_env));
    if (!new)
        return;
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = NULL;
    env_add_back(env, new);
}

void    env_set(t_env **env, char *key, char *value)
{
    if (!env_update(*env, key, value))
        env_add_var(env, key, value);
}
