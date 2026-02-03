/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:28 by mario             #+#    #+#             */
/*   Updated: 2026/02/03 20:42:58 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_valid_unset_option(const char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (0);
	if (s[1] == '\0')
		return (0);
	if (s[1] == '-' && s[2] == '\0')
		return (1);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'f' && s[i] != 'v' && s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	unset_option_error(const char *arg)
{
	ft_putstr_fd("bash: unset: ", 2);
	if (arg[1] == '-')
		ft_putstr_fd("--", 2);
	else
	{
		ft_putstr_fd("-", 2);
		ft_putchar_fd(arg[1], 2);
	}
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("unset: usage: unset [-f] [-v] [-n] [name ...]\n", 2);
}

static int	unset_conflicting_options_error(int opts)
{
	if ((opts & 1) && (opts & 2))
	{
		ft_putstr_fd("bash: unset: cannot simultaneously unset ", 2);
		ft_putstr_fd("a function and a variable\n", 2);
		shell()->exit_code = 1;
		return (1);
	}
	return (0);
}

static void	process_unset_arg(char *arg, int *has_error, int *opts)
{
	if (is_valid_unset_option(arg))
	{
		if (ft_strchr(arg, 'f'))
			*opts |= 1;
		if (ft_strchr(arg, 'v'))
			*opts |= 2;
		return ;
	}
	if (arg[0] == '-' && arg[1] != '\0')
	{
		unset_option_error(arg);
		shell()->exit_code = 2;
		*has_error = 1;
		return ;
	}
	if (env_find(shell()->env, arg))
		env_unset(&shell()->env, arg);
}

int	ft_unset(char **args)
{
	int	i;
	int	has_error;
	int	opts;

	if (!args[1])
		return (shell()->exit_code = 0, 0);
	i = 1;
	has_error = 0;
	opts = 0;
	while (args[i])
	{
		process_unset_arg(args[i], &has_error, &opts);
		if (has_error)
			return (shell()->exit_code);
		i++;
	}
	if (unset_conflicting_options_error(opts))
		return (1);
	if (!has_error)
		shell()->exit_code = 0;
	return (shell()->exit_code);
}
