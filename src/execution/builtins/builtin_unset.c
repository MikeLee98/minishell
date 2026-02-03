/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:28 by mario             #+#    #+#             */
/*   Updated: 2026/02/03 15:19:15 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_valid_unset_option(const char *s)
{
	if (!s)
		return (0);
	if (s[0] != '-')
		return (0);
	if (s[1] == '-' && s[2] == '\0')
		return (1);
	if ((s[1] == 'f' || s[1] == 'v' || s[1] == 'n') && s[2] == '\0')
		return (1);
	return (0);
}

static void	unset_option_error(const char *arg)
{
	ft_putstr_fd("unset: -", 2);
	if (arg && arg[1])
		ft_putchar_fd(arg[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("unset: usage: unset [-f] [-v] [-n] [name ...]\n", 2);
}

int	ft_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && !is_valid_unset_option(args[i]))
		{
			unset_option_error(args[i]);
			shell()->exit_code = 2;
			return (2);
		}
		if (is_valid_unset_option(args[i]))
		{
			i++;
			continue ;
		}
		if (env_find(shell()->env, args[i]))
			env_unset(&shell()->env, args[i]);
		i++;
	}
	shell()->exit_code = 0;
	return (0);
}
