/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:28 by mario             #+#    #+#             */
/*   Updated: 2026/02/03 15:03:31 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] != '\0')
		{
			if (args[i][1] == '-' && args[i][2] == '\0')
			{
				i++;
				continue ;
			}
			ft_putstr_fd("unset: -", 2);
			ft_putchar_fd(args[i][1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			ft_putstr_fd("unset: usage: unset [-f] [-v] [-n] [name ...]\n", 2);
			shell()->exit_code = 2;
			return (2);
		}
		if (env_find(shell()->env, args[i]))
			env_unset(&shell()->env, args[i]);
		i++;
	}
	return (0);
}
