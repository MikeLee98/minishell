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

static int	count_unquoted_len(char *str)
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

static void	copy_unquoted(char *dest, char *src)
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
			quote = src[i];
			i++;
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

static char	*remove_quotes(char *str)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = count_unquoted_len(str);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	copy_unquoted(result, str);
	return (result);
}

void	process_quotes(t_shell *shell)
{
	t_token	*tokens;
	char	*unquoted;

	if (!shell || !shell->toks)
		return ;
	tokens = shell->toks;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			unquoted = remove_quotes(tokens->value);
			free(tokens->value);
			tokens->value = unquoted;
		}
		else if (tokens->type >= TOKEN_REDIR_IN
			&& tokens->type <= TOKEN_REDIR_APPEND)
		{
			if (tokens->next && tokens->next->type == TOKEN_WORD)
			{
				unquoted = remove_quotes(tokens->next->value);
				free(tokens->next->value);
				tokens->next->value = unquoted;
			}
		}
		tokens = tokens->next;
	}
}
