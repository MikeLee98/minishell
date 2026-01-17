#include "../includes/minishell.h"

t_shell	*shell(void)
{
	static t_shell	data;

	return (&data);
}

static int	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	if (!shell->env)
		return (0);
	shell->cmds = NULL;
	shell->toks = NULL;
	shell->exit_code = 0;
	setup_signals();
	return (1);
}

static void	shell_loop(t_shell *shell)
{
	char	*input;
	int		validation_result;

	while (1)
	{
		input = readline("minishell$ ");
		validation_result = validate_input(input);
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
		process_and_execute(shell, input);
		free(input);
	}
}

static void	cleanup_shell(t_shell *shell)
{
	rl_clear_history();
	env_free_all(shell->env);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = shell();
	if (!init_shell(sh, envp))
		return (1);
	shell_loop(sh);
	cleanup_shell(sh);
	return (sh->exit_code);
}
