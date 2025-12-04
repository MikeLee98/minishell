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

static char    *join_key_value(char *key, char *value)
{
    char    *tmp;
    char    *res;

    tmp = ft_strjoin(key, "=");
    if (!tmp)
        return (NULL);
    res = ft_strjoin(tmp, value);
    free(tmp);
    return (res);
}

char    **env_to_array(t_env *env)
{
    char    **array;
    int     count;
    int     i;
	t_env   *head;

    count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return (NULL);

    i = 0;
	env = head;
    while (env)
    {
        array[i] = join_key_value(env->key, env->value);
        i++;
        env = env->next;
    }
    array[i] = NULL;
    return (array);
}
