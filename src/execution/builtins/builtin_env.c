#include "../../../includes/minishell.h"

int	ft_env(void)
{
	t_env	*tmp;

	tmp = shell()->env;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	shell()->exit_code = 0;
	return (0);
}
