#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
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
	int				hd_expand;
	int				wd_split;
	struct s_token	*next;
}	t_token;

// Redirection Structure
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				fd;
	int				hd_expand;
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
	t_token			*toks;
	int				exit_code;
}	t_shell;

extern t_shell *g_shell;

// ************************************************************************** //
//                                  PARSING                                   //
// ************************************************************************** //

// Lexer Functions (lexer.c)
t_token	*create_token(t_token_type type, char *value);
t_token	*lexer(char *input);

// Lexer Utils Functions (lexer_utils.c)
char	*handle_word(char *input, int *i);

// Lexer Helpers Functions (lexer_helpers.c)
int		is_whitespace(char c);
int		is_special_char(char c);

// Syntax Checker Functions (syntax_checker.c)
int		check_syntax(t_shell *shell);

// Parser Functions (parser.c)
void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd);
int		parser(t_shell *shell);

// Parser Utils Functions (parser_utils.c)
t_token	*parse_cmd(t_cmd *cmd, t_token *current);

// Parser Helpers Functions (parser_helpers.c)
void	mark_word_split(t_token *tokens);
void	mark_heredoc_expansion(t_token *tokens);

// Parser Word Split Functions (parser_word_split.c)
void	word_split_tokens(t_token **tokens);

// Expansion Functions (expander.c)
char	*expand_token(t_shell *shell, char *token);
void	expand_tokens(t_shell *shell);

// Expansion Utils Functions (expander_utils.c)
char	*expand_variable(t_shell *shell, char *str, int *i);

// Quote Removal Functions (quote_removal.c)
void	handle_quotes(t_shell *shell);

// Signal Functions (signals.c)
void	setup_signals(void);

// Free Functions (free.c)
void	free_tokens(t_token *tokens);
void	free_split(char **split);
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd *cmd_list);

// ************************************************************************** //
//                                 EXECUTION                                  //
// ************************************************************************** //

// libft_plus
int		ft_strcmp(char *s1, char *s2);
void	ft_itoa_heredoc(int n, char *buffer);

// env_init
t_env	*init_env(char **envp);
void	env_add_back(t_env **env, t_env *new);

// env_set
void	env_set(t_env **env, char *key, char *value, int append);

// env_unset
void	env_unset(t_env **env, char *key);

// env_utils
char	*ft_getenv(t_env *env, char *key);
t_env	*env_find(t_env *env, char *key);
char	**env_to_array(t_env *env);

// free_env
void	env_free_all(t_env *env);
void	free_env_array_nodes(t_env *env);
void	free_env_array(char **array);

// builtin_env
int	ft_env(t_shell *shell);

// builtin_export
int	ft_export(t_shell *shell, char **args);

// builtin_print_export
void	print_export(t_env *env);

// builtin_unset
int	ft_unset(t_shell *shell, char **args);

// builtin_cd
int	ft_cd(t_shell *shell, char **args);

// builtin_pwd
int	ft_pwd(t_shell *shell);

// builtin_echo
int	ft_echo(t_shell *shell, char **args);

// builtin_exit
int	ft_exit(t_shell *shell, char **args);

// exec_main
void	executor(t_shell *shell);
void	execve_with_path(t_shell *shell, t_cmd *cmd);

// exec_single
void	execute_single(t_shell *shell, t_cmd *cmd);

// exec_pipeline
void	execute_pipeline(t_shell *shell, t_cmd *cmd);

// exec_redirect
int		apply_redirections(t_cmd *cmd);

// exec_utils
int		is_builtin(char *cmd);
int		run_builtin(t_shell *shell, char **args);
int		has_slash(char *s);

// heredoc
int		prepare_heredocs(t_shell *shell);

// ************************************************************************** //
//                                   MAIN                                     //
// ************************************************************************** //

// Main Utils Functions (main_utils.c)
int		validate_input(char *input);

// Main Pipeline Functions (main_pipeline.c)
void	process_and_execute(t_shell *shell, char *input);

// Main Debug Functions (main_debug.c)
void	print_debug_info(t_shell *shell);
void	print_tokens(t_token *tokens, char *stage);
void	print_redirections(t_redir *redir);
void	print_cmd_list(t_cmd *cmd_list, char *stage);

// Main Debug Utils Functions (main_debug_utils.c)
void	print_tokens_copy(t_shell *shell, char *stage);

#endif