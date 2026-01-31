/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:04:51 by mario             #+#    #+#             */
/*   Updated: 2026/01/31 19:25:34 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*find_in_path(char **paths, char *cmd_name)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static void	update_underscore_var(char *cmd_name)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	if (ft_strchr(cmd_name, '/'))
	{
		env_set(&shell()->env, "_", cmd_name, 0);
		return ;
	}
	path_env = ft_getenv(shell()->env, "PATH");
	if (!path_env)
	{
		env_set(&shell()->env, "_", cmd_name, 0);
		return ;
	}
	paths = ft_split(path_env, ':');
	full_path = find_in_path(paths, cmd_name);
	if (full_path)
	{
		env_set(&shell()->env, "_", full_path, 0);
		free(full_path);
	}
	else
		env_set(&shell()->env, "_", cmd_name, 0);
	free_split(paths);
}

void	pipeline_child_exec(t_pipeline *p)
{
	setup_signals(SIG_DEFAULT);
	signal(SIGPIPE, SIG_DFL);
	if (p->prev_fd != -1)
	{
		dup2(p->prev_fd, STDIN_FILENO);
		close(p->prev_fd);
	}
	if (p->current->next)
	{
		close(p->pipefd[0]);
		dup2(p->pipefd[1], STDOUT_FILENO);
		close(p->pipefd[1]);
	}
	if (apply_redirections(p->current) != 0)
		exit(1);
	if (is_builtin(p->current->args[0]))
	{
		update_underscore_var(p->current->args[0]);
		exit(run_builtin(p->current->args));
	}
	execve_with_path(p->current);
	exit(127);
}

void	wait_all_pipeline(pid_t last_pid, t_pipeline *p)
{
	pid_t	wait_pid;
	int		last_status;

	last_status = 0;
	wait_pid = wait(&p->status);
	while (wait_pid > 0)
	{
		if (wait_pid == last_pid)
			last_status = p->status;
		wait_pid = wait(&p->status);
	}
	handle_child_status(last_status);
}
