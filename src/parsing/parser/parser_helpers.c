#include "../../../includes/minishell.h"

static int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	mark_heredoc_expansion(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_REDIR_HEREDOC
			&& tokens->next
			&& tokens->next->type == TOKEN_WORD)
		{
			if (has_quotes(tokens->next->value))
				tokens->next->hd_expand = 0;
			else
				tokens->next->hd_expand = 1;
		}
		tokens = tokens->next;
	}
}

void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}
