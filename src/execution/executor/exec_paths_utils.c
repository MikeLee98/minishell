/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:35:07 by mario             #+#    #+#             */
/*   Updated: 2026/02/02 23:15:31 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exit_with_cmd_error(char *cmd_name, const char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	exit(code);
}

static void	execute_local_file(char *local_path, t_cmd *cmd)
{
	char	**envp;

	env_set(&shell()->env, "_", local_path, 0);
	envp = env_to_array(shell()->env);
	execve(local_path, cmd->args, envp);
	free_env_array(envp);
	exit_with_cmd_error(cmd->args[0], ": command not found", 127);
}

static int	validate_local_file(char *local_path, char *cmd_name)
{
	struct stat	st;

	if (stat(local_path, &st) != 0)
		return (0);
	if (S_ISDIR(st.st_mode))
		exit_with_cmd_error(cmd_name, ": Is a directory", 126);
	if (access(local_path, X_OK) != 0)
		exit_with_cmd_error(cmd_name, ": Permission denied", 126);
	return (1);
}

void	execve_without_path(t_cmd *cmd)
{
	char	*local_path;

	local_path = ft_strjoin("./", cmd->args[0]);
	if (!local_path)
		exit_with_cmd_error(cmd->args[0], ": command not found", 127);
	if (validate_local_file(local_path, cmd->args[0]))
		execute_local_file(local_path, cmd);
	free(local_path);
	exit_with_cmd_error(cmd->args[0], ": command not found", 127);
}
