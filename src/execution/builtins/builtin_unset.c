/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:28 by mario             #+#    #+#             */
/*   Updated: 2026/01/21 20:03:29 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (env_find(shell()->env, args[i]))
			env_unset(&shell()->env, args[i]);
		i++;
	}
	shell()->exit_code = 0;
	return (0);
}
