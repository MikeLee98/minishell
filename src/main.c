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
		printf("        Redir: %s %s",
			token_type_str(redir->type), redir->file);
		if (redir->type == TOKEN_REDIR_HEREDOC)
			printf(" (hd_expand: %d)", redir->hd_expand);
		printf("\n");
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
		printf("[%d] Args:\n", cmd_num);
		i = 0;
		while (cmd_list->args && cmd_list->args[i])
		{
			printf("    [%d] = %s\n", i, cmd_list->args[i]);
			i++;
		}
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

static void	print_tokens_copy(t_shell *shell, char *stage)
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


static int	tokenize_and_validate(t_shell *shell, char *input)
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

static void	print_debug_info(t_shell *shell)
{
	if (!shell || !shell->toks)
		return ;
	print_tokens(shell->toks, "TOKENS");
	print_tokens_copy(shell, "TOKENS (after expansion)");
	print_tokens_copy(shell, "TOKENS (after quote removal)");
}

void	run_executor(t_shell *shell)
{
	if (!shell || !shell->cmds)
		return ;
	setup_exec_signals();
	if (prepare_heredocs(shell) < 0)
	{
		shell->exit_code = 130;
		return ;
	}
	executor(shell);
}

static void	process_input(t_shell *shell, char *input)
{
	if (!tokenize_and_validate(shell, input))
		return ;
	print_debug_info(shell);
	if (!parser(shell))
	{
		printf("\nError: Failed to parse tokens.\n\n");
		free_tokens(shell->toks);
		shell->toks = NULL;
		return ;
	}
	print_cmd_list(shell->cmds, "COMMANDS");
	run_executor(shell);
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

	shell.env = init_env(envp);
	shell.cmds = NULL;
	shell.exit_code = 0;
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
		if (!*input)
		{
			free(input);
			continue ;
		}	
		add_history(input);
		process_input(&shell, input);
		free(input);
	}
	rl_clear_history();
	env_free_all(shell.env);
	return (shell.exit_code);
}
