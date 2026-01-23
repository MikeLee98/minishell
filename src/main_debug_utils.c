/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:18:40 by migusant          #+#    #+#             */
/*   Updated: 2026/01/23 19:48:55 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	handle_stage(t_token *copy, char *stage)
{
	t_token	*original;

	original = shell()->toks;
	shell()->toks = copy;
	expand_tokens();
	mark_word_split(shell()->toks);
	if (ft_strncmp(stage, "TOKENS (after word splitting)", 30) == 0)
		word_split_tokens(&shell()->toks);
	else if (ft_strncmp(stage, "TOKENS (after quote removal)", 28) == 0)
	{
		word_split_tokens(&shell()->toks);
		handle_quotes();
	}
	shell()->toks = original;
}

void	print_tokens_copy(char *stage)
{
	t_token	*copy;

	if (!shell() || !shell()->toks)
		return ;
	copy = copy_tokens(shell()->toks);
	if (!copy)
		return ;
	handle_stage(copy, stage);
	print_tokens(copy, stage);
	free_tokens(copy);
}
