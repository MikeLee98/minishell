#include "../../../includes/minishell.h"

static char    *extract_key(char *str)
{
    int     i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    return (ft_substr(str, 0, i));
}

static char    *extract_value(char *str)
{
    int     i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    if (str[i] == '=')
        return (ft_strdup(str + i + 1));
    return (NULL);
}

static t_env   *env_new(char *str)
{
    t_env   *node;

    node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    node->key = extract_key(str);
	    if (!node->key)
    {
        free(node);
        return (NULL);
    }
    node->value = extract_value(str);
	if (node->value == NULL && ft_strchr(str, '='))
    {
        free(node->key);
        free(node);
        return (NULL);
    }
    node->next = NULL;
    return (node);
}

void    env_add_back(t_env **env, t_env *new)
{
    t_env   *tmp;

    if (!*env)
    {
        *env = new;
        return ;
    }
    tmp = *env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

t_env   *init_env(char **envp)
{
    t_env   *env;
	t_env	*new_node;
    int     i;

    env = NULL;
    i = 0;
    while (envp[i])
    {
        new_node = env_new(envp[i]);
        if (!new_node)
        {
            free_env_array_nodes(env);
            return (NULL);
        }
        env_add_back(&env, new_node);
        i++;
    }
    return (env);
}
