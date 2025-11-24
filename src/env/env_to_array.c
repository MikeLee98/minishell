/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 06:25:00 by mario             #+#    #+#             */
/*   Updated: 2025/11/24 12:24:18 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
