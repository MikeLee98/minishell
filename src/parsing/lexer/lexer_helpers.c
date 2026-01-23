#include "../../../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	token->type = type;
	token->value = value;
	token->hd_expand = 0;
	token->wd_split = 0;
	token->next = NULL;
	return (token);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
