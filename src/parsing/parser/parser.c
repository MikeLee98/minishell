#include "../../../includes/minishell.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

static t_token	*build_cmd(t_cmd **cmd_list, t_token *current_token)
{
	t_cmd	*current_cmd;

	current_cmd = create_cmd();
	if (!current_cmd)
	{
		free_cmd_list(*cmd_list);
		return (NULL);
	}
	current_token = parse_cmd(current_cmd, current_token);
	if (!current_token && current_cmd->args == NULL)
	{
		free_cmd(current_cmd);
		return (NULL);
	}
	add_cmd_to_list(cmd_list, current_cmd);
	if (current_token && current_token->type == TOKEN_PIPE)
		current_token = current_token->next;
	return (current_token);
}

t_cmd	*parser(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmd_list;
	t_token	*current_token;

	if (!tokens)
		return (NULL);
	expand_tokens(tokens, shell);
	process_quotes(tokens);
	cmd_list = NULL;
	current_token = tokens;
	while (current_token)
		current_token = build_cmd(&cmd_list, current_token);
	return (cmd_list);
}
