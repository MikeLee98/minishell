#include "../../../includes/minishell.h"

static char *cd_get_target(t_shell *shell, char **args)
{
	char *home;

	if (args[1])
		return (args[1]);
	home = ft_getenv(shell->env, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		shell->exit_code = 1;
		return (NULL);
	}
	return (home);
}

static void	cd_update_env(t_shell *shell, char *oldpwd)
{
	char	*newpwd;

	env_set(&shell->env, "OLDPWD", oldpwd, 0);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return ;
	env_set(&shell->env, "PWD", newpwd, 0);
	free(newpwd);
}

int	ft_cd(t_shell *shell, char **args)
{
	char	*oldpwd;
	char	*target;

	target = cd_get_target(shell, args);
	if (!target)
		return (shell->exit_code);
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(oldpwd);
		shell->exit_code = 1;
		return (1);
	}
	cd_update_env(shell, oldpwd);
	shell->exit_code = 0;
	return (0);
}
