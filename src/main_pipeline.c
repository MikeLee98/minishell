/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:18:36 by migusant          #+#    #+#             */
/*   Updated: 2026/02/02 15:55:42 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	tokenize_and_validate(char *input)
{
	shell()->toks = lexer(input);
	if (!shell()->toks)
		return (0);
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
	if (MINISHELL_DEBUG)
		print_debug_info();
	if (!parser())
	{
		free_tokens(shell()->toks);
		shell()->toks = NULL;
		return ;
	}
	if (shell()->cmds)
	{
		if (MINISHELL_DEBUG)
			print_cmd_list(shell()->cmds, "COMMANDS");
		run_executor();
	}
	free_tokens(shell()->toks);
	shell()->toks = NULL;
	free_cmd_list(shell()->cmds);
	shell()->cmds = NULL;
}
