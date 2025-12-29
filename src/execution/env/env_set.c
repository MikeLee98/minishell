#include "../../../includes/minishell.h"

static int env_update(t_env *env, char *key, char *new_value, int append)
{
    t_env *node;
	char *tmp;

    node = env_find(env, key);
    if (!node)
		return (0);
    if (new_value == NULL && !append)
    {
        free(node->value);
        node->value = NULL;
        return (1);
    }
	tmp = ft_strdup(new_value);
	if (!tmp)
		return (1);
	if (append && node->value)
	{
		tmp = ft_strjoin(node->value, new_value);
		if (!tmp)
			return (1);
		free(node->value);
		node->value = tmp;
		return (1);
	}
    free(node->value);
    node->value = tmp;
    return (1);
}

static void    env_add_var(t_env **env, char *key, char *value)
{
    t_env   *new;

    new = malloc(sizeof(t_env));
    if (!new)
		return;
	new->key = ft_strdup(key);
    if (!new->key)
    {
        free(new);
        return;
    }
	if (value)
    {
        new->value = ft_strdup(value);
        if (!new->value)
        {
            free(new->key);
            free(new);
            return;
        }
    }
    else
        new->value = NULL;
    new->next = NULL;
    env_add_back(env, new);
}

void    env_set(t_env **env, char *key, char *value, int append)
{
    if (!env_update(*env, key, value, append))
        env_add_var(env, key, value);
}
