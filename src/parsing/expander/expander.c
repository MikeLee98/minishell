#include "../../../includes/minishell.h"

static char	*process_expansion_char(char *str, int *i, char **result,
	char **envp)
{
	char	*temp;
	char	*var_expansion;
	char	char_str[2];

	if (str[*i] == '$')
	{
		var_expansion = expand_variable(str, i, envp);
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

static char	*expand_in_double_quotes(char *str, int *i, char **envp)
{
	char	*result;
	char	*temp;

	(*i)++;
	result = ft_strdup("\"");
	while (str[*i] && str[*i] != '"')
		process_expansion_char(str, i, &result, envp);
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

static char	*expand_token(char *token, char **envp)
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
			segment = expand_in_double_quotes(token, &i, envp);
		else
			segment = expand_variable(token, &i, envp);
		temp = ft_strjoin(result, segment);
		free(result);
		free(segment);
		result = temp;
	}
	return (result);
}

void	expand_tokens(t_token *tokens, char **envp)
{
	char	*expanded;

	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			expanded = expand_token(tokens->value, envp);
			free(tokens->value);
			tokens->value = expanded;
		}
		else if (tokens->type >= TOKEN_REDIR_IN
			&& tokens->type <= TOKEN_REDIR_APPEND)
		{
			if (tokens->next && tokens->next->type == TOKEN_WORD)
			{
				expanded = expand_token(tokens->next->value, envp);
				free(tokens->next->value);
				tokens->next->value = expanded;
			}
		}
		tokens = tokens->next;
	}
}
