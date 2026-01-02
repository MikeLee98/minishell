#include "../../../includes/minishell.h"

static int plus_equal_pos(char *arg)
{
    int i = 0;

    while (arg[i] && arg[i] != '=')
    {
        if (arg[i] == '+' && arg[i + 1] == '=')
            return i;
        i++;
    }
    return -1;
}

static void split_key_value(char *arg, char **key, char **value, int *append)
{
    int pos;

	*append = 0;
	pos = plus_equal_pos(arg);
	if (pos >= 0)
	{
		*append = 1;
		*key = ft_substr(arg, 0, pos);
		if (!*key)
			return ;
		*value = ft_strdup(arg + pos + 2);
		if (!*value)
			return ;
		return ;
	}
    pos = 0;
    while (arg[pos] && arg[pos] != '=')
        pos++;
    *key = ft_substr(arg, 0, pos);
	if (!*key)
		return;
    if (arg[pos] == '=')
	{
        *value = ft_strdup(arg + pos + 1);
		if (!*value)
			return ;
	}
    else
        *value = NULL;
}

static void export_assign(t_env **env, char *arg)
{
    char	*key;
    char	*value;
	int 	append;

    split_key_value(arg, &key, &value, &append);
    if (!key)
		return ;
	if (value == NULL)
	{
        if (!env_find(*env, key))
            env_set(env, key, NULL, 0);
    }
	else
		env_set(env, key, value, append);
    free(key);
    free(value);
}

static int is_valid_identifier(char *s)
{
    int i;

    if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
        return (0);
    i = 1;
    while (s[i] && s[i] != '=')
    {
		if (s[i] == '+' && s[i + 1] == '=')
			break ;
        if (!ft_isalnum(s[i]) && s[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

void ft_export(t_shell *shell, char **args)
{
	int	i;

	if (!args[1])
	{
		print_export(shell->env);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
			export_assign(&shell->env, args[i]);
		i++;
	}
}
