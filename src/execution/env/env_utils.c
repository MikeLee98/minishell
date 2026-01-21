/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:55:46 by mario             #+#    #+#             */
/*   Updated: 2026/01/21 19:55:47 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char *join_key_value(char *key, char *value)
{
    char *tmp;
    char *res;

	if (!value)
        return (ft_strdup(key));
    tmp = ft_strjoin(key, "=");
    if (!tmp)
        return (NULL);
    res = ft_strjoin(tmp, value);
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

void update_shlvl(void)
{
    char *shlvl_str = ft_getenv(shell()->env, "SHLVL");
    int shlvl = 1;

    if (shlvl_str)
    {
        shlvl = ft_atoi(shlvl_str) + 1;
        if (shlvl < 0)
            shlvl = 0;
    }

    char buffer[16];
    ft_itoa_buffer(shlvl, buffer);
    env_set(&shell()->env, "SHLVL", buffer, 0);
}
