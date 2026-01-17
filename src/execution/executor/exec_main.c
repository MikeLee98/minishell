#include "../../../includes/minishell.h"

void executor(void)
{
	if (!shell()->cmds)
		return ;

	if (!shell()->cmds->next)
		execute_single(shell()->cmds);
	else
		execute_pipeline(shell()->cmds);
}

void execve_with_path(t_cmd *cmd)
{
	char	**paths;
	char	*full_path;
	char	*path_env;
	char	**envp;
	int		i;
	char	*tmp;

	envp = env_to_array(shell()->env);
	if (has_slash(cmd->args[0]))
	{
		execve(cmd->args[0], cmd->args, envp);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		if (errno == EACCES)
			exit(126);
		exit(127);
	}
	path_env = ft_getenv(shell()->env, "PATH");
	if (!path_env)
	{
		execve(cmd->args[0], cmd->args, envp);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			exit(1);
		full_path = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		if (!full_path)
			exit(1);
		execve(full_path, cmd->args, envp);
		free(full_path);
		i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}
