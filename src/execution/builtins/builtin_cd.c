#include "../../../includes/minishell.h"

static char *cd_get_target(t_shell *shell, char **args)
{
	char *home;

	if (args[1])
		return (args[1]);
	home = ft_getenv(shell->env, "HOME");
	if (!home)
	{
		ft_printf("minishell: cd: HOME not set\n");
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

void	ft_cd(t_shell *shell, char **args)
{
	char	*oldpwd;
	char	*target;

	target = cd_get_target(shell, args);
	if (!target)
		return ;
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		ft_printf("minishell: cd: %s: %s\n", target, strerror(errno));
		free(oldpwd);
		return ;
	}
	cd_update_env(shell, oldpwd);
}
