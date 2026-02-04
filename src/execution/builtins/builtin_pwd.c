/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:56:25 by mario             #+#    #+#             */
/*   Updated: 2026/02/04 13:05:21 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (!shell()->stderr_redir)
		{
			ft_putstr_fd("minishell: pwd: error retrieving current ", 2);
			ft_putstr_fd("directory\n", 2);
		}
		shell()->exit_code = 1;
		return (1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	shell()->exit_code = 0;
	return (0);
}
