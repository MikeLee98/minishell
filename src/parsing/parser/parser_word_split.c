#include "../../../includes/minishell.h"

static void	insert_split_tokens(t_token *current, char **words)
{
	t_token	*new_token;
	t_token	*prev;
	int		i;

	if (!words || !words[0])
		return ;
	free(current->value);
	current->value = ft_strdup(words[0]);
	current->wd_split = 0;
	prev = current;
	i = 1;
	while (words[i])
	{
		new_token = create_token(TOKEN_WORD, ft_strdup(words[i]));
		if (new_token)
		{
			new_token->next = prev->next;
			prev->next = new_token;
			prev = new_token;
		}
		i++;
	}
}

void	word_split_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	char	**words;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD && current->wd_split == 1)
		{
			words = ft_split(current->value, ' ');
			if (words)
			{
				insert_split_tokens(current, words);
				free_split(words);
			}
		}
		current = next;
	}
}
