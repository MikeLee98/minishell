/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:19:56 by mario             #+#    #+#             */
/*   Updated: 2026/01/31 19:27:02 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_cmd_error(char *cmd_name, const char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	exit(code);
}

static void	try_paths(char **paths, t_cmd *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;
	char	**new_envp;

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
			new_envp = env_to_array(shell()->env);
			execve(full_path, cmd->args, new_envp);
			free_env_array(new_envp);
		}
		free(full_path);
		i++;
	}
}

static void	execve_absolute_path(t_cmd *cmd)
{
	char		**envp;
	struct stat	st;

	if (stat(cmd->args[0], &st) != 0)
		print_cmd_error(cmd->args[0], ": No such file or directory", 127);
	if (S_ISDIR(st.st_mode))
		print_cmd_error(cmd->args[0], ": Is a directory", 126);
	if (access(cmd->args[0], X_OK) != 0)
		print_cmd_error(cmd->args[0], ": Permission denied", 126);
	env_set(&shell()->env, "_", cmd->args[0], 0);
	envp = env_to_array(shell()->env);
	execve(cmd->args[0], cmd->args, envp);
	free_env_array(envp);
	print_cmd_error(cmd->args[0], ": No such file or directory", 127);
}

static void	execve_search_path(t_cmd *cmd, char *path_env)
{
	char	**paths;
	char	**envp;

	if (!path_env)
		path_env = ".";
	paths = ft_split(path_env, ':');
	if (!paths)
		print_cmd_error(cmd->args[0], ": command not found", 127);
	envp = env_to_array(shell()->env);
	try_paths(paths, cmd);
	free_split(paths);
	free_env_array(envp);
	print_cmd_error(cmd->args[0], ": command not found", 127);
}

void	execve_with_path(t_cmd *cmd)
{
	char	*path_env;

	if (ft_strchr(cmd->args[0], '/'))
		execve_absolute_path(cmd);
	path_env = ft_getenv(shell()->env, "PATH");
	execve_search_path(cmd, path_env);
}
