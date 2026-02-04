/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:21 by mario             #+#    #+#             */
/*   Updated: 2026/02/03 22:20:05 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	sort_array(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_escaped_value(const char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\\' || value[i] == '"'
			|| value[i] == '$' || value[i] == '`')
			printf("\\");
		printf("%c", value[i]);
		i++;
	}
}

static void	print_env_entry(char *entry)
{
	char	*value;

	value = ft_strchr(entry, '=');
	if (value)
	{
		*value = '\0';
		if (ft_strcmp(entry, "_") != 0)
		{
			printf("declare -x %s=\"", entry);
			print_escaped_value(value + 1);
			printf("\"\n");
		}
		*value = '=';
	}
	else if (ft_strcmp(entry, "_") != 0)
		printf("declare -x %s\n", entry);
}

void	print_export(t_env *env)
{
	char	**envp;
	int		i;

	envp = env_to_array(env);
	if (!envp)
		return ;
	sort_array(envp);
	i = 0;
	while (envp[i])
	{
		print_env_entry(envp[i]);
		i++;
	}
	free_env_array(envp);
}
