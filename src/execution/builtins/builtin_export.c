/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:17 by mario             #+#    #+#             */
/*   Updated: 2026/01/22 18:14:00 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	plus_equal_pos(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	split_key_value(char *arg, t_env *tmp, int *append)
{
	int	pos;

	tmp->key = NULL;
	tmp->value = NULL;
	*append = 0;
	pos = plus_equal_pos(arg);
	if (pos >= 0)
	{
		*append = 1;
		tmp->key = ft_substr(arg, 0, pos);
		if (!tmp->key)
			return ;
		tmp->value = ft_strdup(arg + pos + 2);
		if (!tmp->value)
			return ;
		return ;
	}
	pos = 0;
	while (arg[pos] && arg[pos] != '=')
		pos++;
	tmp->key = ft_substr(arg, 0, pos);
	if (!tmp->key)
		return ;
	if (arg[pos] == '=')
		tmp->value = ft_strdup(arg + pos + 1);
}

static void	export_assign(t_env **env, char *arg)
{
	t_env	tmp;
	int		append;

	split_key_value(arg, &tmp, &append);
	if (!tmp.key)
		return ;
	if (!tmp.value)
	{
		if (!env_find(*env, tmp.key))
			env_set(env, tmp.key, NULL, 0);
	}
	else
		env_set(env, tmp.key, tmp.value, append);
	free(tmp.key);
	free(tmp.value);
}

static int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			break ;
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(char **args)
{
	int	i;

	if (!args[1])
	{
		print_export(shell()->env);
		shell()->exit_code = 0;
		return (shell()->exit_code);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			shell()->exit_code = 1;
		}
		else
			export_assign(&shell()->env, args[i]);
		i++;
	}
	if (shell()->exit_code != 1)
		shell()->exit_code = 0;
	return (shell()->exit_code);
}
