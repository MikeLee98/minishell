/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:06 by mario             #+#    #+#             */
/*   Updated: 2026/01/21 19:56:07 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_env(void)
{
	t_env	*tmp;

    if (shell()->cmds->args[1])
    {
        ft_putendl_fd("env: too many arguments", 2);
        shell()->exit_code = 1;
        return (1);
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
