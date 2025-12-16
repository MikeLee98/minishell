#include "../../../includes/minishell.h"

void	ft_unset(t_shell *shell, char **args)
{
	int i = 1;

	while (args[i])
	{
		if (env_find(shell->env, args[i]))
			env_unset(&shell->env, args[i]);
		i++;
	}
}
