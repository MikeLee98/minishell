#include "../../../includes/minishell.h"

static int	parse_exit_code(const char *s, long *out)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		if (result > (LONG_MAX - (*s - '0')) / 10)
			return (0);
		result = result * 10 + (*s - '0');
		s++;
	}
	*out = result * sign;
	return (1);
}

int	ft_exit(t_shell *shell, char **args)
{
	long	code;

	ft_putstr_fd("exit\n", 1);
	if (!args[1])
		exit(shell->exit_code);

	if (!parse_exit_code(args[1], &code))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_code = 1;
		return (1);
	}
	exit((unsigned char)code);
}
