#include "../../../includes/minishell.h"

static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

static void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	char	**new_args;
	int		i;
	int		count;

	if (!arg || !*arg)
		return ;
	count = count_args(cmd->args);
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

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

static void	add_redir_to_cmd(t_cmd *cmd, t_token_type type, char *file, int hd_expand)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	new_redir->fd = -1;
	new_redir->hd_expand = hd_expand;
	new_redir->next = NULL;
	if (!cmd->redirections)
	{
		cmd->redirections = new_redir;
		return ;
	}
	current = cmd->redirections;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

t_token	*parse_cmd(t_cmd *cmd, t_token *current)
{
	int	hd_expand;

	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_WORD)
		{
			add_arg_to_cmd(cmd, current->value);
			current = current->next;
		}
		else if (current->type >= TOKEN_REDIR_IN
			&& current->type <= TOKEN_REDIR_HEREDOC)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
				return (NULL);
			
			hd_expand = current->next->hd_expand;
			add_redir_to_cmd(cmd, current->type, current->next->value, hd_expand);
			current = current->next->next;
		}
		else
			current = current->next;
	}
	return (current);
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
