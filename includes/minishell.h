#ifndef MINISHELL_H
# define MINISHELL_H

#include "../../libft/libft.h"
#include <stdlib.h>

typedef struct s_shell {
	t_env   *env;
	int	exit_status;
} t_shell;

typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;

//env
t_env   *init_env(char **envp);
void    env_set(t_env **env, char *key, char *value);
void    env_unset(t_env **env, char *key);
char    *env_get_value(t_env *env, char *key);
t_env   *env_find(t_env *env, char *key);
char    **env_to_array(t_env *env);
void    env_add_back(t_env **env, t_env *new);

//built_ins
void	ft_env(t_shell *shell, char **args);
void 	ft_export(t_env **env, char **args);

#endif
