#include "../../../includes/minishell.h"

static int has_plus_equal(char *arg)
{
    int i = 0;

    while (arg[i])
    {
        if (arg[i] == '+' && arg[i + 1] == '=')
            return 1;
        i++;
    }
    return 0;
}

static void split_key_value(char *arg, char **key, char **value)
{
    int i;

    i = 0;
    while (arg[i] && arg[i] != '=')
        i++;
    *key = ft_substr(arg, 0, i);
	if (!*key)
		return;
    if (arg[i] == '=')
	{
        *value = ft_strdup(arg + i + 1);
		if (!*value)
			return;
	}
    else
        *value = NULL;
}

static void export_assign(t_env **env, char *arg)
{
    char *key;
    char *value;

    split_key_value(arg, &key, &value);
	if (value == NULL)
	{
        if (!env_find(*env, key))
            env_set(env, key, NULL);
    }
    else
		env_set(env, key, value);
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
        if (!ft_isalnum(s[i]) && s[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

void ft_export(t_shell *shell, char **args)
{
    int i;

    if (!args[1])
    {
        print_export(shell->env);
        return ;
    }
    i = 1;
    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
            ft_printf("minishell: export: `%s': not a valid identifier\n", args[i]);
        else
            export_assign(&shell->env, args[i]);
        i++;
    }
}
