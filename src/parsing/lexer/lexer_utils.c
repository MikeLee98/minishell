#include "../../../includes/parsing.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static char	*extract_quoted(char *input, int *i, char quote)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
		(*i)++;
	len = *i - start;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, input + start, len + 1);
	return (word);
}

static char	*extract_unquoted(char *input, int *i)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_char(input[*i]) && !is_quote(input[*i]))
		(*i)++;
	len = *i - start;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, input + start, len + 1);
	return (word);
}

char	*extract_word(char *input, int *i)
{
	char	*word;

	if (is_quote(input[*i]))
	{
		if (input[*i] == '\'')
			word = extract_quoted(input, i, '\'');
		else
			word = extract_quoted(input, i, '"');
	}
	else
		word = extract_unquoted(input, i);
	return (word);
}
