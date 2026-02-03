/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 10:13:17 by mario             #+#    #+#             */
/*   Updated: 2026/02/03 19:56:14 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_valid_identifier(char *s)
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

void	export_identifier_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	is_valid_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	if (arg[1] == '\0')
		return (0);
	if (arg[1] == '-' && arg[2] == '\0')
		return (1);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'f' && arg[i] != 'n' && arg[i] != 'p')
			return (0);
		i++;
	}
	return (1);
}

void	export_option_error(char *arg)
{
	ft_putstr_fd("bash: export: ", 2);
	if (arg[1] == '-')
		ft_putstr_fd("--", 2);
	else
	{
		ft_putstr_fd("-", 2);
		ft_putchar_fd(arg[1], 2);
	}
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("export: usage: export [-fn] [name[=value] ...] ", 2);
	ft_putstr_fd("or export -p\n", 2);
}

void	export_function_error(char *arg)
{
	ft_putstr_fd("bash: export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a function\n", 2);
	shell()->exit_code = 1;
}
