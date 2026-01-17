#include "../../../includes/minishell.h"

static char	*handle_expansion_char(char *str, int *i,
	char **result)
{
	char	*expansion;

	if (str[*i] == '$')
	{
		expansion = expand_variable(str, i);
		*result = append_string(*result, expansion, 1);
	}
	else
	{
		*result = append_char(*result, str[*i]);
		(*i)++;
	}
	return (*result);
}

char	*expand_double_quotes(char *str, int *i)
{
	char	*result;

	(*i)++;
	result = ft_strdup("\"");
	if (!result)
		return (NULL);
	while (str[*i] && str[*i] != '"')
	{
		if (!handle_expansion_char(str, i, &result))
			return (NULL);
	}
	if (str[*i] == '"')
	{
		result = append_char(result, '"');
		if (!result)
			return (NULL);
		(*i)++;
	}
	return (result);
}

char	*expand_single_quotes(char *str, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
