#include "../../../includes/minishell.h"

int	ft_unset(t_shell *shell, char **args)
{
	int i = 1;

	while (args[i])
	{
		if (env_find(shell->env, args[i]))
			env_unset(&shell->env, args[i]);
		i++;
	}
	shell->exit_code = 0;
	return (0);
}
