#include "../../../includes/minishell.h"

static char	*get_env_value(char *var_name)
{
	char	*value;

	if (!var_name || !var_name[0])
		return (ft_strdup(""));
	else if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(shell()->exit_code));
	else if (ft_strlen(var_name) == 1 && !ft_isalnum(var_name[0])
		&& var_name[0] != '_')
		return (ft_strdup(""));
	value = ft_getenv(shell()->env, var_name);
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
	char	special[2];

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	if (ft_isdigit(str[*i]))
	{
		special[0] = str[*i];
		special[1] = '\0';
		(*i)++;
		return (ft_strdup(special));
	}
	if (str[*i] && !ft_isalnum(str[*i]) && str[*i] != '_')
	{
		special[0] = str[*i];
		special[1] = '\0';
		(*i)++;
		return (ft_strdup(special));
	}
	return (extract_regular_var_name(str, i));
}

static char	*expand_dollar_var(char *str, int *i)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_var_name(str, i);
	if (!var_name || !var_name[0])
	{
		free(var_name);
		return (ft_strdup("$"));
	}
	var_value = get_env_value(var_name);
	free(var_name);
	return (var_value);
}

static int	is_valid_var_start(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

char	*expand_variable(char *str, int *i)
{
	char	char_str[2];

	if (str[*i] == '\\' && str[*i + 1])
	{
		char_str[0] = str[*i + 1];
		char_str[1] = '\0';
		(*i) += 2;
		return (ft_strdup(char_str));
	}
	if (str[*i] == '$')
	{
		if (str[*i + 1] && is_valid_var_start(str[*i + 1]))
			return (expand_dollar_var(str, i));
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
