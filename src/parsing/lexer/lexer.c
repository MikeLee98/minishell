#include "../../../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->hd_expand = 0;
	token->wd_split = 0;
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

static int	handle_operator(t_token **head, char *input, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	if (input[*i] == '|')
		new_token = create_token(TOKEN_PIPE, ft_strdup("|"));
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		new_token = create_token(TOKEN_REDIR_HEREDOC, ft_strdup("<<"));
		(*i)++;
	}
	else if (input[*i] == '<')
		new_token = create_token(TOKEN_REDIR_IN, ft_strdup("<"));
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		new_token = create_token(TOKEN_REDIR_APPEND, ft_strdup(">>"));
		(*i)++;
	}
	else if (input[*i] == '>')
		new_token = create_token(TOKEN_REDIR_OUT, ft_strdup(">"));
	if (!new_token)
		return (0);
	add_token(head, new_token);
	return (1);
}

static int	handle_token(t_token **head, char *input, int *i)
{
	char	*word;

	if (is_special_char(input[*i]))
	{
		if (!handle_operator(head, input, i))
			return (0);
		(*i)++;
	}
	else
	{
		word = handle_word(input, i);
		if (!word)
			return (0);
		add_token(head, create_token(TOKEN_WORD, word));
	}
	return (1);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (!handle_token(&head, input, &i))
		{
			free_tokens(head);
			return (NULL);
		}
	}
	return (head);
}
