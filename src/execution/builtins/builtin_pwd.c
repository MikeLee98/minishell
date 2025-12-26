#include "../../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf("minishell: pwd: error retrieving current directory\n");
		return ;
	}
	ft_printf("%s\n", cwd);
	free(cwd);
}
