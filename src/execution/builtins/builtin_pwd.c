#include "../../../includes/minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory\n", 2);
		shell->exit_code = 1;
		return (1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	shell->exit_code = 0;
	return (0);
}
