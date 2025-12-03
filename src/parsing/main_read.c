#include "../../includes/parsing.h"
#include <readline/readline.h>
#include <readline/history.h>

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

static void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	printf("\nTOKENS:\n");
	while (tokens)
	{
		printf("[%d] Type: %-15s Value: %s\n",
			i, token_type_str(tokens->type), tokens->value);
		tokens = tokens->next;
		i++;
	}
	printf("\n");
}

static void	print_redirections(t_redir *redir)
{
	while (redir)
	{
		printf("      Redir: %s %s\n",
			token_type_str(redir->type), redir->file);
		redir = redir->next;
	}
}

static void	print_cmd_list(t_cmd *cmd_list)
{
	int	cmd_num;
	int	i;

	cmd_num = 0;
	printf("COMMANDS:\n");
	while (cmd_list)
	{
		printf("[%d] Args: ", cmd_num);
		i = 0;
		while (cmd_list->args && cmd_list->args[i])
		{
			printf("%s ", cmd_list->args[i]);
			i++;
		}
		printf("\n");
		if (cmd_list->redirections)
			print_redirections(cmd_list->redirections);
		cmd_list = cmd_list->next;
		cmd_num++;
	}
	printf("\n");
}

static void	process_input(char *input)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	if (!input || !*input)
		return ;
	tokens = lexer(input);
	if (!tokens)
	{
		printf("Error: Failed to tokenize input.\n");
		return ;
	}
	print_tokens(tokens);
	cmd_list = parser(tokens);
	if (!cmd_list)
	{
		printf("Error: Failed to parse tokens.\n");
		free_tokens(tokens);
		return ;
	}
	print_cmd_list(cmd_list);
	free_tokens(tokens);
	free_cmd_list(cmd_list);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		process_input(input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
