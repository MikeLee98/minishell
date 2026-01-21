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
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			env_set(&shell()->env, "PWD", cwd, 0);
			free(cwd);
		}
		env_set(&shell()->env, "PATH", "/usr/local/bin:/usr/bin:/bin", 0);
	}
	shell()->cmds = NULL;
	shell()->toks = NULL;
	shell()->exit_code = 0;
	shell()->should_exit = 0;
	update_shlvl();
	setup_signals();
	return (1);
}

// static char	*ft_strjoin_char(char *s, char c)
// {
// 	char	*result;
// 	size_t	len;
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	len = ft_strlen(s);
// 	result = malloc(len + 2);
// 	if (!result)
// 		return (free(s), NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		result[i] = s[i];
// 		i++;
// 	}
// 	result[i] = c;
// 	result[i + 1] = '\0';
// 	return (result);
// }

// static char	*read_line_no_buffer(int fd)
// {
// 	char	buffer[1];
// 	char	*line;
// 	char	*tmp;
// 	int		ret;

// 	line = ft_strdup("");
// 	if (!line)
// 		return (NULL);
// 	while (1)
// 	{
// 		ret = read(fd, buffer, 1);
// 		if (ret <= 0)
// 		{
// 			if (ft_strlen(line) == 0)
// 				return (free(line), NULL);
// 			return (line);
// 		}
// 		if (buffer[0] == '\n')
// 			return (line);
// 		tmp = line;
// 		line = ft_strjoin_char(tmp, buffer[0]);
// 		free(tmp);
// 		if (! line)
// 			return (NULL);
// 	}
// }

// static void	shell_loop(void)
// {
// 	char	*input;
// 	int		validation_result;

// 	while (1)
// 	{
// 		if (isatty(STDIN_FILENO))
// 			input = readline("minishell$ ");
// 		else
// 			input = read_line_no_buffer(STDIN_FILENO);
// 		if (!input)
// 			break ;
// 		validation_result = validate_input(input);
// 		if (validation_result == 1)
// 		{
// 			free(input);
// 			break ;
// 		}
// 		else if (validation_result == 2)
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		if (! *input)
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		if (isatty(STDIN_FILENO))
// 			add_history(input);
// 		process_and_execute(input);
// 		free(input);
// 		if (shell()->should_exit)
// 			break;
// 	}
// }

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

void	cleanup_shell(void)
{
	// printf("DEBUG: Cleaning up shell...\n");
	rl_clear_history();
	if (shell()->toks)
		free_tokens(shell()->toks);
	if (shell()->cmds)
		free_cmd_list(shell()->cmds);
	free_env_nodes(shell()->env);
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
