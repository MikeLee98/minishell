#include "../includes/minishell.h"

static char	*token_type_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_REDIR_IN)
		return ("REDIR_IN");
	else if (type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == TOKEN_REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (type == TOKEN_REDIR_HEREDOC)
		return ("REDIR_HEREDOC");
	return ("UNKNOWN");
}

void	print_tokens(t_token *tokens, char *stage)
{
	int	i;

	i = 0;
	printf("\n%s:\n", stage);
	while (tokens)
	{
		printf("[%d] Type: %-15s Value: %s\n",
			i, token_type_str(tokens->type), tokens->value);
		tokens = tokens->next;
		i++;
	}
}

static t_token	*copy_tokens(t_token *tokens)
{
	t_token	*copy;
	t_token	*current;
	t_token	*new_token;
	t_token	*last;

	copy = NULL;
	last = NULL;
	current = tokens;
	while (current)
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->type = current->type;
		new_token->value = ft_strdup(current->value);
		new_token->next = NULL;
		if (!copy)
			copy = new_token;
		else
			last->next = new_token;
		last = new_token;
		current = current->next;
	}
	return (copy);
}

void	print_tokens_copy(t_shell *shell, char *stage)
{
	t_shell	temp_shell;
	t_token	*copy;

	if (!shell || !shell->toks)
		return ;
	copy = copy_tokens(shell->toks);
	if (!copy)
		return ;
	temp_shell.env = shell->env;
	temp_shell.exit_code = shell->exit_code;
	temp_shell.toks = copy;
	temp_shell.cmds = NULL;
	if (ft_strncmp(stage, "TOKENS (after expansion)", 24) == 0)
		expand_tokens(&temp_shell);
	else if (ft_strncmp(stage, "TOKENS (after quote removal)", 28) == 0)
	{
		expand_tokens(&temp_shell);
		process_quotes(&temp_shell);
	}
	print_tokens(temp_shell.toks, stage);
	free_tokens(temp_shell.toks);
}

void	print_redirections(t_redir *redir)
{
	while (redir)
	{
		printf("        Redir: %s %s",
			token_type_str(redir->type), redir->file);
		if (redir->type == TOKEN_REDIR_HEREDOC)
			printf(" (hd_expand: %d)", redir->hd_expand);
		printf("\n");
		redir = redir->next;
	}
}
