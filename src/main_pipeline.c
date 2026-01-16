#include "../includes/minishell.h"

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

static void	run_executor(t_shell *shell)
{
	if (!shell || !shell->cmds)
		return ;
	if (prepare_heredocs(shell) < 0)
	{
		shell->exit_code = 130;
		return ;
	}
	executor(shell);
}

void	process_and_execute(t_shell *shell, char *input)
{
	if (!tokenize_and_validate(shell, input))
		return ;
	// print_debug_info(shell);
	if (!parser(shell))
	{
		printf("\nError: Failed to parse tokens.\n\n");
		free_tokens(shell->toks);
		shell->toks = NULL;
		return ;
	}
	// print_cmd_list(shell->cmds, "COMMANDS");
	run_executor(shell);
	free_tokens(shell->toks);
	shell->toks = NULL;
	free_cmd_list(shell->cmds);
	shell->cmds = NULL;
}
