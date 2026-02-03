/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:19:56 by mario             #+#    #+#             */
/*   Updated: 2026/02/02 23:15:36 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	execute_at_path(char *path, t_cmd *cmd)
{
	char	**envp;

	env_set(&shell()->env, "_", path, 0);
	envp = env_to_array(shell()->env);
	execve(path, cmd->args, envp);
	free_env_array(envp);
}

static void	execute_absolute_path(t_cmd *cmd)
{
	struct stat	st;

	if (stat(cmd->args[0], &st) != 0)
		exit_with_cmd_error(cmd->args[0], ": No such file or directory", 127);
	if (S_ISDIR(st.st_mode))
		exit_with_cmd_error(cmd->args[0], ": Is a directory", 126);
	if (access(cmd->args[0], X_OK) != 0)
		exit_with_cmd_error(cmd->args[0], ": Permission denied", 126);
	execute_at_path(cmd->args[0], cmd);
	exit_with_cmd_error(cmd->args[0], ": No such file or directory", 127);
}

static void	search_path_dirs(char **paths, t_cmd *cmd)
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
			execute_at_path(full_path, cmd);
		free(full_path);
		i++;
	}
}

static void	execute_from_path_var(t_cmd *cmd, char *path_env)
{
	char	**paths;

	if (!path_env)
	{
		execve_without_path(cmd);
		return ;
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		exit_with_cmd_error(cmd->args[0], ": command not found", 127);
	search_path_dirs(paths, cmd);
	free_split(paths);
	exit_with_cmd_error(cmd->args[0], ": command not found", 127);
}

void	execve_with_path(t_cmd *cmd)
{
	char	*path_env;

	if (ft_strchr(cmd->args[0], '/'))
		execute_absolute_path(cmd);
	path_env = ft_getenv(shell()->env, "PATH");
	execute_from_path_var(cmd, path_env);
}
