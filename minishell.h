#ifndef ENV_H
# define ENV_H

#include "../libft/libft.h"
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

// struct s_cmd{
// 	char	**command
// 	t_red	*input
// 	char	**output
// 	char **filename
// 	struct s_commands *next;
// } t_cmd;

//env
t_env   *init_env(char **envp);
void    env_add_back(t_env **env, t_env *new);
t_env   *env_new(char *str);
char    *extract_value(char *str);
char    *extract_key(char *str);
void    env_set(t_env **env, char *key, char *value);
void    env_unset(t_env **env, char *key);
char    *env_get_value(t_env *env, char *key);
t_env   *env_find(t_env *env, char *key);
char    **env_to_array(t_env *env);

//built_ins
void	ft_env(char **args, t_env *env);


#endif
