/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:25 by mario             #+#    #+#             */
/*   Updated: 2026/02/19 14:38:27 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 4096);
	if (!cwd)
	{
		ft_putstr_fd("minishell: pwd: error retrieving current ", 2);
		ft_putstr_fd("directory\n", 2);
		return (1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
