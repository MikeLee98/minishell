/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:17 by mario             #+#    #+#             */
/*   Updated: 2026/02/03 19:57:15 by migusant         ###   ########.fr       */
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

static void	process_export_arg(char *arg, int *has_error, int *opts)
{
	if (is_valid_option(arg))
	{
		if (ft_strchr(arg, 'f'))
			*opts |= 1;
		if (ft_strcmp(arg, "--") == 0 || ft_strchr(arg, 'n')
			|| ft_strchr(arg, 'p'))
			*opts |= 2;
		return ;
	}
	if (arg[0] == '-' && arg[1] != '\0')
	{
		export_option_error(arg);
		shell()->exit_code = 2;
		*has_error = 1;
	}
	else if (!is_valid_identifier(arg))
	{
		export_identifier_error(arg);
		shell()->exit_code = 1;
		*has_error = 1;
	}
	else
		export_assign(&shell()->env, arg);
}

int	ft_export(char **args)
{
	int	i;
	int	has_error;
	int	opts;

	if (!args[1])
		return (print_export(shell()->env), shell()->exit_code = 0, 0);
	i = 1;
	has_error = 0;
	opts = 0;
	while (args[i])
	{
		process_export_arg(args[i], &has_error, &opts);
		i++;
	}
	if ((opts & 1) && i > 2)
	{
		export_function_error(args[i - 1]);
		return (1);
	}
	if ((opts & 2) && !(opts & 1) && i == 2)
		print_export(shell()->env);
	if (!has_error)
		shell()->exit_code = 0;
	return (shell()->exit_code);
}
