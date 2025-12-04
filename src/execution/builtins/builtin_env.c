#include "../minishell.h"

void	ft_env(t_shell *shell, char **args)
{
	t_env	*tmp;

	if (args && args[0])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exit_status = 127;
		return ;
	}
	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
