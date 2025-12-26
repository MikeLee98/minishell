#include "../../../includes/minishell.h"

static char	*get_env_value(t_shell *shell, char *var_name)
{
	char	*value;

	if (!var_name)
		return (ft_strdup(""));
	if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(shell->exit_code));
	else if (ft_strlen(var_name) == 1 && !ft_isalnum(var_name[0]))
		return (ft_strdup(""));
	value = ft_getenv(shell->env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static char	*extract_regular_var_name(char *str, int *i)
{
	int		start;
	int		len;

	start = *i;
	if (str[*i] && (ft_isalpha(str[*i]) || str[*i] == '_'))
	{
		(*i)++;
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
	}
	len = *i - start;
	return (ft_substr(str, start, len));
}

static char	*extract_var_name(char *str, int *i)
{
	int		start;
	char	special[2];

	(*i)++;
	if (str[*i] && !ft_isalnum(str[*i]) && str[*i] != '_')
	{
		special[0] = str[*i];
		special[1] = '\0';
		(*i)++;
		return (ft_strdup(special));
	}
	if (ft_isdigit(str[*i]))
	{
		start = *i;
		(*i)++;
		return (ft_substr(str, start, 1));
	}
	return (extract_regular_var_name(str, i));
}

static char	*expand_dollar_var(t_shell *shell, char *str, int *i)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_var_name(str, i);
	var_value = get_env_value(shell, var_name);
	free(var_name);
	return (var_value);
}

char	*expand_variable(t_shell *shell, char *str, int *i)
{
	char	char_str[2];

	if (str[*i] == '$')
	{
		if (str[*i + 1])
			return (expand_dollar_var(shell, str, i));
		else
		{
			char_str[0] = '$';
			char_str[1] = '\0';
			(*i)++;
			return (ft_strdup(char_str));
		}
	}
	else
	{
		char_str[0] = str[*i];
		char_str[1] = '\0';
		(*i)++;
		return (ft_strdup(char_str));
	}
}
