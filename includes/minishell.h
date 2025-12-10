#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"
#include <stdlib.h>

// Token Types
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
}	t_token_type;

// Token Structure
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

// Redirection Structure
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

// Command Structure
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}	t_cmd;

// Environment Structure
typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;

// Shell Structure
typedef struct s_shell {
	t_env   *env;
	t_cmd   *cmds;
} t_shell;

//libft_plus
int ft_strcmp(char *s1, char *s2);

//env_init
t_env   *init_env(char **envp);
void    env_add_back(t_env **env, t_env *new);

//env_set
void    env_set(t_env **env, char *key, char *value);

//env_unset
void    env_unset(t_env **env, char *key);

//env_utils
char    *ft_getenv(t_env *env, char *key);
t_env   *env_find(t_env *env, char *key);

//builtin_env
void	ft_env(t_shell *shell);

//builtin_export
void ft_export(t_shell *shell, char **args);

//pint_export
void    print_export(t_env *env);

//builtin_unset
void	ft_unset(t_shell *shell, char **args);

//builtin_cd
void	ft_cd(t_shell *shell, char **args);

//builtin_pwd
void	ft_pwd(void);

//builtin_echo
void	ft_echo(char **args);

#endif
