/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 21:50:46 by mario             #+#    #+#             */
/*   Updated: 2025/11/24 12:35:00 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int env_update(t_env *env, char *key, char *new_value)
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
