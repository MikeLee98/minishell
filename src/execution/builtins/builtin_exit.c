#include "../../../includes/minishell.h"

static int is_numeric(const char *s)
{
	int i = 0;

	if (!s || !s[0])
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static long long ft_atoll_overflow(const char *s, int *overflow)
{
	long long sign = 1;
	unsigned long long res = 0;
	unsigned long long limit = LLONG_MAX;

	*overflow = 0;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s)
	{
		if (res > (limit - (*s - '0')) / 10)
		{
			*overflow = 1;
			return (0);
		}
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res * sign);
}

void    ft_exit(t_shell *shell, char **args)
{
    long long   code;
    int         overflow;

    ft_printf("exit\n");
    if (!args[1])
        exit(shell->exit_code);

    if (!is_numeric(args[1]))
    {
        ft_printf("minishell: exit: %s: numeric argument required\n", args[1]);
        exit(255);
    }
    code = ft_atoll_overflow(args[1], &overflow);
    if (overflow)
    {
        ft_printf("minishell: exit: %s: numeric argument required\n", args[1]);
        exit(255);
    }
    if (args[2])
    {
        ft_printf("minishell: exit: too many arguments\n");
        shell->exit_code = 1;
        return ;
    }
    exit((unsigned char)code);
}
