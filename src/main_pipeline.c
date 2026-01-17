#include "../includes/minishell.h"

static int	tokenize_and_validate(char *input)
{
	shell()->toks = lexer(input);
	if (!shell()->toks)
	{
		printf("Error: Failed to tokenize input.\n");
		return (0);
	}
	if (!check_syntax())
	{
		free_tokens(shell()->toks);
		shell()->toks = NULL;
		return (0);
	}
	return (1);
}

static void	run_executor(void)
{
	if (!shell() || !shell()->cmds)
		return ;
	if (prepare_heredocs() < 0)
	{
		shell()->exit_code = 130;
		return ;
	}
	executor();
}

void	process_and_execute(char *input)
{
	if (!tokenize_and_validate(input))
		return ;
	// print_debug_info();
	if (!parser())
	{
		printf("\nError: Failed to parse tokens.\n\n");
		free_tokens(shell()->toks);
		shell()->toks = NULL;
		return ;
	}
	// print_cmd_list(shell()->cmds, "COMMANDS");
	run_executor();
	free_tokens(shell()->toks);
	shell()->toks = NULL;
	free_cmd_list(shell()->cmds);
	shell()->cmds = NULL;
}
