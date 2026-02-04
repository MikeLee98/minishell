/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:06 by mario             #+#    #+#             */
/*   Updated: 2026/02/04 19:03:47 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int ft_env(char **args)
{
	t_env	*tmp;

	if (args[1])
	{
		if (!shell()->stderr_redir)
		{
			ft_putstr_fd("env: ‘", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd("’: No such file or directory\n", 2);
		}
		shell()->exit_code = 127;
		return (127);
	}
	tmp = shell()->env;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	shell()->exit_code = 0;
	return (0);
}
