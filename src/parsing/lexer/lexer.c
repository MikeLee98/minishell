#include "../../../includes/parsing.h"

static t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

static void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

static int	handle_operator(char *input, int *i, t_token **head)
{
	if (input[*i] == '|')
		add_token(head, create_token(TOKEN_PIPE, ft_strdup("|")));
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(head, create_token(TOKEN_REDIR_HEREDOC, ft_strdup("<<")));
		(*i)++;
	}
	else if (input[*i] == '<')
		add_token(head, create_token(TOKEN_REDIR_IN, ft_strdup("<")));
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(head, create_token(TOKEN_REDIR_APPEND, ft_strdup(">>")));
		(*i)++;
	}
	else if (input[*i] == '>')
		add_token(head, create_token(TOKEN_REDIR_OUT, ft_strdup(">")));
	else
		return (0);
	return (1);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	int		i;
	char	*word;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_special_char(input[i]))
		{
			if (!handle_operator(input, &i, &head))
				return (free_tokens(head), NULL);
			i++;
		}
		else
		{
			word = extract_word(input, &i);
			if (word)
				add_token(&head, create_token(TOKEN_WORD, word));
		}
	}
	return (head);
}
