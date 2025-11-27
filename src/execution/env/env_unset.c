#include "../minishell.h"

void    env_unset(t_env **env, char *key)
{
    t_env *tmp;
    t_env *prev;

    tmp = *env;
    prev = NULL;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key) + 1) == 0)
        {
            if (prev)
                prev->next = tmp->next;
            else
                *env = tmp->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}
