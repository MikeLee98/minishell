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

static char *join_key_value(char *key, char *value)
{
    char *tmp;
    char *res;

    tmp = ft_strjoin(key, "=");
    if (!tmp)
        return (NULL);
    if (value)
        res = ft_strjoin(tmp, value);
    else
        res = ft_strdup(tmp);
    free(tmp);
    return (res);
}

char    **env_to_array(t_env *env)
{
    char    **envp;
    int     count;
    int     i;
	t_env   *head;

	head = env;
    count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return (NULL);
    i = 0;
	env = head;
    while (env)
    {
        envp[i] = join_key_value(env->key, env->value);
		if (!envp[i])
		{
			free_env_array(envp);
			return (NULL);
		}
        i++;
        env = env->next;
    }
    envp[i] = NULL;
    return (envp);
}
