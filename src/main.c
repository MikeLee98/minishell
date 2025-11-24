/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:44:30 by marioro2          #+#    #+#             */
/*   Updated: 2025/11/24 12:48:58 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"

// imagina que todas as funções já estão implementadas:
// init_env, env_find, env_get_value, env_update,
// env_add_var, env_set, env_unset, env_to_array,...

static void    env_free_node(t_env *node)
{
    if (!node)
        return;
    free(node->key);
    free(node->value);
    free(node);
}

static void    env_free_all(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env->next;
        env_free_node(env);
        env = tmp;
    }
}

static void    free_env_array(char **array)
{
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

int main(int ac, char **av, char **envp)
{
    t_env *env;
    char **array;
    t_env *tmp;
	int i;

	i = 0;
    env = init_env(envp);

    printf("HOME = %s\n", env_get_value(env, "HOME"));
    printf("PATH = %s\n", env_get_value(env, "PATH"));

    env_update(env, "HOME", "/tmp/test_home");
    printf("HOME (depois update) = %s\n", env_get_value(env, "HOME"));

    env_set(&env, "TESTVAR", "12345");
    printf("TESTVAR (nova) = %s\n", env_get_value(env, "TESTVAR"));

    env_unset(&env, "TESTVAR");
    printf("TESTVAR (unser depois) = %s\n",
        env_get_value(env, "TESTVAR"));

    array = env_to_array(env);
    printf("\n--- ENV ARRAY ---\n");
    while (array[i])
        printf("%s\n", array[i++]);

    free_env_array(array);
	env_free_all(env);

    return (0);
}
