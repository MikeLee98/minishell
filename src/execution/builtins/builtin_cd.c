/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:55:59 by mario             #+#    #+#             */
/*   Updated: 2026/02/04 13:00:45 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	cd_update_env(char *oldpwd)
{
	char	*newpwd;

	env_set(&shell()->env, "OLDPWD", oldpwd, 0);
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		env_set(&shell()->env, "PWD", newpwd, 0);
		free(newpwd);
	}
	free(oldpwd);
}

static int	cd_chdir_and_update(char *target, char *oldpwd, int should_free)
{
	if (chdir(target) != 0)
	{
		if (!shell()->stderr_redir)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(target, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
		}
		free(oldpwd);
		if (should_free)
			free(target);
		shell()->exit_code = 1;
		return (1);
	}
	return (0);
}

int	ft_cd(char **args)
{
	char	*oldpwd;
	char	*target;
	int		should_free;
	int		print_pwd;

	target = cd_get_target(args, &should_free, &print_pwd);
	if (!target)
		return (shell()->exit_code);
	oldpwd = getcwd(NULL, 0);
	if (cd_chdir_and_update(target, oldpwd, should_free))
		return (1);
	if (print_pwd)
	{
		ft_putstr_fd(target, 1);
		ft_putstr_fd("\n", 1);
	}
	cd_update_env(oldpwd);
	if (should_free)
		free(target);
	shell()->exit_code = 0;
	return (0);
}
