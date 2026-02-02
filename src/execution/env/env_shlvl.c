/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:30:33 by mario             #+#    #+#             */
/*   Updated: 2026/02/02 19:31:49 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_shlvl_warning(int shlvl)
{
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putnbr_fd(shlvl, 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
}

void	update_shlvl(void)
{
	char	*shlvl_str;
	int		shlvl;
	char	buffer[16];

	shlvl_str = ft_getenv(shell()->env, "SHLVL");
	shlvl = 1;
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str) + 1;
		if (shlvl >= 1000)
		{
			print_shlvl_warning(shlvl);
			shlvl = 1;
		}
		else if (shlvl < 0)
			shlvl = 0;
	}
	ft_itoa_buffer(shlvl, buffer);
	env_set(&shell()->env, "SHLVL", buffer, 0);
}
