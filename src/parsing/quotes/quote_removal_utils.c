#include "../../../includes/minishell.h"

static int	skip_quotes(char *str, int *i)
{
	char	quote;
	int		len;

	quote = str[(*i)++];
	len = 0;
	while (str[*i] && str[*i] != quote)
	{
		len++;
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
	return (len);
}

int	count_unquoted_len(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			len += skip_quotes(str, &i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	copy_unquoted(char *dest, char *src)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '"')
		{
			quote = src[i++];
			while (src[i] && src[i] != quote)
				dest[j++] = src[i++];
			if (src[i] == quote)
				i++;
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
}
