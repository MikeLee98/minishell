#include "../../../includes/minishell.h"

static char	*process_expansion_char(t_shell *shell, char *str, int *i,
	char **result)
{
	char	*temp;
	char	*var_expansion;
	char	char_str[2];

	if (str[*i] == '$')
	{
		var_expansion = expand_variable(shell, str, i);
		temp = ft_strjoin(*result, var_expansion);
		free(*result);
		free(var_expansion);
		*result = temp;
	}
	else
	{
		char_str[0] = str[*i];
		char_str[1] = '\0';
		temp = ft_strjoin(*result, char_str);
		free(*result);
		*result = temp;
		(*i)++;
	}
	return (*result);
}

static char	*expand_in_double_quotes(t_shell *shell, char *str, int *i)
{
	char	*result;
	char	*temp;

	(*i)++;
	result = ft_strdup("\"");
	while (str[*i] && str[*i] != '"')
		process_expansion_char(shell, str, i, &result);
	if (str[*i] == '"')
	{
		temp = ft_strjoin(result, "\"");
		free(result);
		result = temp;
		(*i)++;
	}
	return (result);
}

static char	*expand_in_single_quotes(char *str, int *i)
{
	char	*result;
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	result = ft_substr(str, start, *i - start);
	return (result);
}

static char	*expand_token(t_shell *shell, char *token)
{
	char	*result;
	char	*temp;
	char	*segment;
	int		i;

	if (!token)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			segment = expand_in_single_quotes(token, &i);
		else if (token[i] == '"')
			segment = expand_in_double_quotes(shell, token, &i);
		else
			segment = expand_variable(shell, token, &i);
		temp = ft_strjoin(result, segment);
		free(result);
		free(segment);
		result = temp;
	}
	return (result);
}

void	expand_tokens(t_shell *shell)
{
	t_token	*tokens;
	char	*expanded;

	if (!shell || !shell->toks)
		return ;
	tokens = shell->toks;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			expanded = expand_token(shell, tokens->value);
			free(tokens->value);
			tokens->value = expanded;
		}
		else if (tokens->type >= TOKEN_REDIR_IN
			&& tokens->type <= TOKEN_REDIR_APPEND)
		{
			if (tokens->next && tokens->next->type == TOKEN_WORD)
			{
				expanded = expand_token(shell, tokens->next->value);
				free(tokens->next->value);
				tokens->next->value = expanded;
			}
		}
		tokens = tokens->next;
	}
}
