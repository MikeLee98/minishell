/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:19:04 by mario             #+#    #+#             */
/*   Updated: 2025/11/24 12:35:29 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
