#include "../includes/minishell.h"

static t_token	*create_token_copy(t_token *current)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(current->value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = current->type;
	new_token->hd_expand = current->hd_expand;
	new_token->wd_split = current->wd_split;
	new_token->next = NULL;
	return (new_token);
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
		new_token = create_token_copy(current);
		if (!new_token)
		{
			free_tokens(copy);
			return (NULL);
		}
		if (!copy)
			copy = new_token;
		else
			last->next = new_token;
		last = new_token;
		current = current->next;
	}
	return (copy);
}

static void	handle_stage(t_shell *temp_shell, char *stage)
{
	expand_tokens(temp_shell);
	mark_word_split(temp_shell->toks);
	if (ft_strncmp(stage, "TOKENS (after word splitting)", 30) == 0)
		word_split_tokens(&temp_shell->toks);
	else if (ft_strncmp(stage, "TOKENS (after quote removal)", 28) == 0)
	{
		word_split_tokens(&temp_shell->toks);
		handle_quotes(temp_shell);
	}
}

void	print_tokens_copy(char *stage)
{
	t_shell	temp_shell;
	t_token	*copy;

	if (!shell() || !shell()->toks)
		return ;
	copy = copy_tokens(shell()->toks);
	if (!copy)
		return ;
	temp_shell.env = shell()->env;
	temp_shell.exit_code = shell()->exit_code;
	temp_shell.toks = copy;
	temp_shell.cmds = NULL;
	handle_stage(&temp_shell, stage);
	print_tokens(temp_shell.toks, stage);
	free_tokens(temp_shell.toks);
}
