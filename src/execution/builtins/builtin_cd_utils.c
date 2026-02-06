/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:18:48 by mario             #+#    #+#             */
/*   Updated: 2026/02/05 22:37:32 by migusant         ###   ########.fr       */
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

static char	*handle_special_args(char **args, int i, int *should_free,
	int *print_pwd)
{
	if (args[i] && ft_strcmp(args[i], "-") == 0)
	{
		*print_pwd = 1;
		return (get_env_var("OLDPWD"));
	}
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

char	*cd_get_target(char **args, int *should_free, int *print_pwd)
{
	int		i;

	i = 1;
	*should_free = 0;
	*print_pwd = 0;
	if (!parse_cd_flags(args, &i))
		return (NULL);
	if (args[i] && args[i + 1])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell()->exit_code = 1;
		return (NULL);
	}
	return (handle_special_args(args, i, should_free, print_pwd));
}
