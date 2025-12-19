#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>

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
	int				fd;
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
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// Shell Structure
typedef struct s_shell
{
	t_env			*env;
	t_cmd			*cmds;
	int				exit_code;
}	t_shell;

// ************************************************************************** //
//                                  PARSING                                   //
// ************************************************************************** //

// Lexer Functions (lexer.c)
t_token	*lexer(char *input);

// Lexer Helper Functions (lexer_utils.c)
char	*handle_word(char *input, int *i);

// Lexer Helper Functions (lexer_utils_gen.c)
int		is_whitespace(char c);
int		is_special_char(char c);

// Syntax Checker Functions
int		check_syntax(t_token *tokens);

// Parser Functions (parser.c)
t_cmd	*parser(t_token *tokens, char **envp);

// Parser Helper Functions (parser_utils.c)
t_token	*parse_cmd(t_cmd *cmd, t_token *current);
void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd);

// Expansion Functions (expander.c)
void	expand_tokens(t_token *tokens, char **envp);

// Expansion Helper Functions (expander_utils.c)
char	*expand_variable(char *str, int *i, char **envp);

// Quote Removal Functions (quote_removal.c)
void	process_quotes(t_token *tokens);

// Signal Functions (signals.c)
void	setup_signals(void);

// Free Functions (free.c)
void	free_tokens(t_token *tokens);
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd *cmd_list);

// ************************************************************************** //
//                                 EXECUTION                                  //
// ************************************************************************** //

//libft_plus
int		ft_strcmp(char *s1, char *s2);
void ft_itoa_heredoc(int n, char *buffer);

//env_init
t_env	*init_env(char **envp);
void	env_add_back(t_env **env, t_env *new);

//env_set
void	env_set(t_env **env, char *key, char *value);

//env_unset
void	env_unset(t_env **env, char *key);

//env_utils
char	*ft_getenv(t_env *env, char *key);
t_env	*env_find(t_env *env, char *key);
char    **env_to_array(t_env *env);

//free_env
void    env_free_all(t_env *env);
void 	free_env_array_nodes(t_env *env);
void    free_env_array(char **array);

//builtin_env
void	ft_env(t_shell *shell);

//builtin_export
void	ft_export(t_shell *shell, char **args);

//builtin_print_export
void	print_export(t_env *env);

//builtin_unset
void	ft_unset(t_shell *shell, char **args);

//builtin_cd
void	ft_cd(t_shell *shell, char **args);

//builtin_pwd
void	ft_pwd(void);

//builtin_echo
void	ft_echo(char **args);

//builin_exit
void	ft_exit(t_shell *shell, char **args);

//exec_main
void	executor(t_shell *shell);
void 	execve_with_path(t_shell *shell, t_cmd *cmd);

//exec_single
void	execute_single(t_shell *shell, t_cmd *cmd);

//exec_pipeline
void	execute_pipeline(t_shell *shell, t_cmd *cmd);

//exec_redirect
int		apply_redirections(t_cmd *cmd);

//exec_utils
int		is_builtin(char *cmd);
int		run_builtin(t_shell *shell, char **args);
int		builtin_needs_parent(char *cmd);
int 	has_slash(char *s);

//heredoc
int		prepare_heredocs(t_cmd *cmds);

//signals
void    setup_exec_signals(void);

#endif
