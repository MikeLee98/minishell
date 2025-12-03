#include "../../../includes/parsing.h"

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

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_token	*current_token;

	cmd_list = NULL;
	current_token = tokens;
	while (current_token)
	{
		current_cmd = create_cmd();
		if (!current_cmd)
			return (free_cmd_list(cmd_list), NULL);
		current_token = parse_single_cmd(current_cmd, current_token);
		if (!current_token && current_cmd->args == NULL)
		{
			free_cmd(current_cmd);
			break ;
		}
		add_cmd_to_list(&cmd_list, current_cmd);
		if (current_token && current_token->type == TOKEN_PIPE)
			current_token = current_token->next;
	}
	return (cmd_list);
}
