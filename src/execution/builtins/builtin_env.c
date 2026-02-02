/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:06 by mario             #+#    #+#             */
/*   Updated: 2026/02/02 21:06:50 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_env(void)
{
	t_env	*tmp;

    if (shell()->cmds->args[1])
    {
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(shell()->cmds->args[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
        return (127);
    }
	tmp = shell()->env;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
