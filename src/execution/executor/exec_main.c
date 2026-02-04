/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:54:59 by mario             #+#    #+#             */
/*   Updated: 2026/02/04 19:05:09 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	executor(void)
{
	if (!shell()->cmds)
		return ;
	if (!shell()->cmds->next)
		execute_single(shell()->cmds);
	else
		execute_pipeline(shell()->cmds);
}

int	run_builtin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args));
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(args));
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	return (1);
}
