#include "../includes/minishell.h"

t_shell	*shell(void)
{
	static t_shell	data;

	return (&data);
}

static int	init_shell(char **envp)
{
	char	*cwd;

	shell()->env = init_env(envp);
	if (!shell()->env)
	{
		shell()->env = NULL;
		env_set(&shell()->env, "SHLVL", "1", 0);
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			env_set(&shell()->env, "PWD", cwd, 0);
			free(cwd);
		}
		env_set(&shell()->env, "PATH", "/usr/local/bin:/usr/bin:/bin", 0);
		env_set(&shell()->env, "_", "/usr/bin/env", 0);
	}
	shell()->cmds = NULL;
	shell()->toks = NULL;
	shell()->exit_code = 0;
	update_shlvl();
	setup_signals();
	return (1);
}

static void	shell_loop(void)
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
		process_and_execute(input);
		free(input);
	}
}

static void	cleanup_shell(void)
{
	rl_clear_history();
	env_free_all(shell()->env);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!init_shell(envp))
		return (1);
	shell_loop();
	cleanup_shell();
	return (shell()->exit_code);
}
