/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:54:59 by mario             #+#    #+#             */
/*   Updated: 2026/01/30 12:24:02 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	executor(void)
{
	if (!shell()->cmds)
		return ;
	if (!shell()->cmds->next)
		execute_single(shell()->cmds);
	else
		execute_pipeline(shell()->cmds);
}

int	run_builtin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args));
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env());
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	return (1);
}

static void	try_paths(char **paths, t_cmd *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	*full_path;

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
		if (access(full_path, X_OK) == 0)
		{
			env_set(&shell()->env, "_", full_path, 0);
			free_env_array(envp);
			envp = env_to_array(shell()->env);
			execve(full_path, cmd->args, envp);
		}
		free(full_path);
		i++;
	}
}

static void	print_cmd_error(char *cmd_name, const char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	exit(code);
}

void	execve_with_path(t_cmd *cmd)
{
	char		**paths;
	char		*path_env;
	char		**envp;
	struct stat	st;

	if (ft_strchr(cmd->args[0], '/'))
	{
		if (stat(cmd->args[0], &st) != 0)
			print_cmd_error(cmd->args[0], ": No such file or directory", 127);
		if (S_ISDIR(st.st_mode))
			print_cmd_error(cmd->args[0], ": Is a directory", 126);
		if (access(cmd->args[0], X_OK) != 0)
			print_cmd_error(cmd->args[0], ": Permission denied", 126);
		env_set(&shell()->env, "_", cmd->args[0], 0);
		envp = env_to_array(shell()->env);
		execve(cmd->args[0], cmd->args, envp);
		print_cmd_error(cmd->args[0], ": No such file or directory", 127);
	}
	path_env = ft_getenv(shell()->env, "PATH");
	if (!path_env)
		print_cmd_error(cmd->args[0], ": command not found", 127);
	paths = ft_split(path_env, ':');
	envp = env_to_array(shell()->env);
	try_paths(paths, cmd, envp);
	print_cmd_error(cmd->args[0], ": command not found", 127);
}
