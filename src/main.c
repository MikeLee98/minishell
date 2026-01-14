#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

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
		if (g_signal_received)
		{
			shell->exit_code = g_signal_received;
			g_signal_received = 0;
		}
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
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (!init_shell(&shell, envp))
		return (1);
	shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.exit_code);
}
