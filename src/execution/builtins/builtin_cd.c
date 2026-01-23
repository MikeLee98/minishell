/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:55:59 by mario             #+#    #+#             */
/*   Updated: 2026/01/21 19:56:00 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_env_var(char *var_name)
{
	char	*value;

	value = ft_getenv(shell()->env, var_name);
	if (!value)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(var_name, 2);
		ft_putstr_fd(" not set\n", 2);
		shell()->exit_code = 1;
		return (NULL);
	}
	return (value);
}

static int	parse_cd_flags(char **args, int *i)
{
	while (args[*i] && args[*i][0] == '-' && args[*i][1])
	{
		if (ft_strcmp(args[*i], "--") == 0)
		{
			(*i)++;
			break ;
		}
		else if (ft_strcmp(args[*i], "-") == 0)
			break ;
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(args[*i], 2);
			ft_putstr_fd(": invalid option\n", 2);
			shell()->exit_code = 2;
			return (0);
		}
	}
	return (1);
}

static char	*cd_get_target(char **args, int *should_free)
{
	int		i;

	i = 1;
	*should_free = 0;
	if (!parse_cd_flags(args, &i))
		return (NULL);
	if (args[i] && ft_strcmp(args[i], "-") == 0)
		return (get_env_var("OLDPWD"));
	if (!args[i] || !args[i][0])
	{
		if (i > 1 || (args[i] && !args[i][0]))
		{
			*should_free = 1;
			return (ft_strdup("."));
		}
		return (get_env_var("HOME"));
	}
	if (ft_strcmp(args[i], "~") == 0)
		return (get_env_var("HOME"));
	return (args[i]);
}

static void	cd_update_env(char *oldpwd)
{
	char	*newpwd;

	env_set(&shell()->env, "OLDPWD", oldpwd, 0);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return ;
	env_set(&shell()->env, "PWD", newpwd, 0);
	free(newpwd);
}

int	ft_cd(char **args)
{
	char	*oldpwd;
	char	*target;
	int		should_free;

	target = cd_get_target(args, &should_free);
	if (!target)
		return (shell()->exit_code);
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(oldpwd);
		if (should_free)
			free(target);
		return (shell()->exit_code = 1, 1);
	}
	cd_update_env(oldpwd);
	if (should_free)
		free(target);
	return (shell()->exit_code = 0, 0);
}
