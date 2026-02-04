/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:11 by mario             #+#    #+#             */
/*   Updated: 2026/02/04 17:16:57 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_overflow(unsigned long result, int digit, int sign)
{
	unsigned long	limit;

	if (sign == -1)
		limit = -(unsigned long)LONG_MIN;
	else
		limit = LONG_MAX;
	if (result > (limit - digit) / 10)
		return (1);
	return (0);
}

static int	parse_exit_code(const char *s, long *out)
{
	unsigned long	result;
	int				sign;

	result = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		if (check_overflow(result, *s - '0', sign))
			return (0);
		result = result * 10 + (*s - '0');
		s++;
	}
	*out = result * sign;
	return (1);
}

static int	exit_numeric_error(char *arg)
{
	if (!shell()->stderr_redir)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	shell()->should_exit = 1;
	shell()->exit_code = 2;
	return (2);
}

static int	exit_too_many_args(void)
{
	if (!shell()->stderr_redir)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	shell()->exit_code = 1;
	return (1);
}

int	ft_exit(char **args)
{
	long	code;

	ft_putstr_fd("exit\n", 1);
	if (!args[1])
	{
		shell()->should_exit = 1;
		return (shell()->exit_code);
	}
	if (!parse_exit_code(args[1], &code))
		return (exit_numeric_error(args[1]));
	if (args[2])
		return (exit_too_many_args());
	shell()->should_exit = 1;
	shell()->exit_code = (unsigned char)code;
	return ((unsigned char)code);
}
