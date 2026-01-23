#include "../../../includes/minishell.h"

static char	*dup_char_and_advance(char c, int *i)
{
	char	char_str[2];

	char_str[0] = c;
	char_str[1] = '\0';
	(*i)++;
	return (ft_strdup(char_str));
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
	(*i)++;
	if (str[*i] == '?')
		return (dup_char_and_advance('?', i));
	if (ft_isdigit(str[*i]))
		return (dup_char_and_advance(str[*i], i));
	if (str[*i] && !ft_isalnum(str[*i]) && str[*i] != '_')
		return (dup_char_and_advance(str[*i], i));
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

char	*expand_variable(char *str, int *i)
{
	if (str[*i] == '\\' && str[*i + 1])
	{
		(*i)++;
		return (dup_char_and_advance(str[*i], i));
	}
	else if (str[*i] == '$')
	{
		if (str[*i + 1] && (ft_isalnum(str[*i + 1])
				|| str[*i + 1] == '_' || str[*i + 1] == '?'))
			return (expand_dollar_var(str, i));
		else
			return (dup_char_and_advance('$', i));
	}
	else
		return (dup_char_and_advance(str[*i], i));
}
