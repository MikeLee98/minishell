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

static void	print_redirections(t_redir *redir)
{
	while (redir)
	{
		printf("      Redir: %s %s\n",
			token_type_str(redir->type), redir->file);
		redir = redir->next;
	}
}

static void	print_cmd_list(t_cmd *cmd_list, char *stage)
{
	int	cmd_num;
	int	i;

	cmd_num = 0;
	printf("\n%s:\n", stage);
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

static void	print_tokens(t_token *tokens, char *stage)
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

static void	print_tokens_copy(t_token *tokens, char *stage, t_shell *shell)
{
	t_token	*copy;

	copy = copy_tokens(tokens);
	if (!copy)
		return ;
	if (ft_strncmp(stage, "TOKENS (after expansion)", 24) == 0)
		expand_tokens(copy, shell);
	else if (ft_strncmp(stage, "TOKENS (after quote removal)", 28) == 0)
	{
		expand_tokens(copy, shell);
		process_quotes(copy);
	}
	print_tokens(copy, stage);
	free_tokens(copy);
}

static int	tokenize_and_validate(char *input, t_shell *shell)
{
	shell->toks = lexer(input);
	if (!shell->toks)
	{
		printf("Error: Failed to tokenize input.\n");
		return (0);
	}
	if (!check_syntax(shell))
	{
		free_tokens(shell->toks);
		shell->toks = NULL;
		return (0);
	}
	return (1);
}

static void	print_debug_info(t_token *tokens, t_shell *shell)
{
	print_tokens(tokens, "TOKENS");
	print_tokens_copy(tokens, "TOKENS (after expansion)", shell);
	print_tokens_copy(tokens, "TOKENS (after quote removal)", shell);
}

void	run_executor(t_shell *shell, t_cmd *cmd_list)
{
	shell->cmds = cmd_list;
	setup_exec_signals();
	if (prepare_heredocs(cmd_list) < 0)
	{
		shell->exit_code = 130;
		return ;
	}
	executor(shell);
}

static void	process_input(char *input, t_shell *shell)
{
	if (!tokenize_and_validate(input, shell))
		return ;
	print_debug_info(shell->toks, shell);
	if (!parser(shell))
	{
		printf("\nError: Failed to parse tokens.\n\n");
		free_tokens(shell->toks);
		shell->toks = NULL;
		return ;
	}
	print_cmd_list(shell->cmds, "COMMANDS");
	run_executor(shell, shell->cmds);
	free_tokens(shell->toks);
	shell->toks = NULL;
	free_cmd_list(shell->cmds);
	shell->cmds = NULL;
}

static char	get_unclosed_quote_type(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (!str[i])
				return (quote);
			i++;
		}
		else
			i++;
	}
	return (0);
}

static void	print_unclosed_quote_error(char quote)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
}

static int	handle_input_validation(char *input)
{
	char	unclosed_quote;

	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	else if (ft_strncmp(input, "exit", 5) == 0)
	{
		free(input);
		return (1);
	}
	unclosed_quote = get_unclosed_quote_type(input);
	if (unclosed_quote)
	{
		print_unclosed_quote_error(unclosed_quote);
		free(input);
		return (2);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;
	int		validation_result;

	(void)argc;
	(void)argv;	
	shell.env = init_env(envp);
	if (!shell.env)
		return (1);
	shell.cmds = NULL;
	shell.toks = NULL;
	shell.exit_code = 0;
	setup_signals();
	while (1)
	{
		input = readline("minishell$ ");
		validation_result = handle_input_validation(input);
		if (validation_result == 1)
			break ;
		else if (validation_result == 2)
			continue ;
		if (*input)
			add_history(input);
		process_input(input, &shell);
		free(input);
	}
	rl_clear_history();
	env_free_all(shell.env);
	return (0);
}
