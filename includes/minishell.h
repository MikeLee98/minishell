#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"
#include <stdlib.h>

typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_shell {
	t_env   *env;
	int	exit_status;
} t_shell;

//env_init
t_env   *init_env(char **envp);
void    env_add_back(t_env **env, t_env *new);

//env_set
void    env_set(t_env **env, char *key, char *value);

//env_unset
void    env_unset(t_env **env, char *key);

//env_utils
char    *env_get_value(t_env *env, char *key);
t_env   *env_find(t_env *env, char *key);

//builtin_env
void	ft_env(t_shell *shell, char **args);

//builtin_export
void 	ft_export(t_env **env, char **args);

#endif
