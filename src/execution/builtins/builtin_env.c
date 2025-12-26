#include "../../../includes/minishell.h"

void	ft_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		else
			ft_printf("%s\n", tmp->key); //NULL value case -> for testing
		tmp = tmp->next;
	}
}
