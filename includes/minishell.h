/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:52:17 by mario             #+#    #+#             */
/*   Updated: 2026/02/02 19:32:53 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

// Enable Debug Mode
# define MINISHELL_DEBUG	0

// Signal Modes
# define SIG_INTERACTIVE	0
# define SIG_IGNORE			1
# define SIG_DEFAULT		2
# define SIG_HEREDOC		3

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

// Pipeline Structure
typedef struct s_pipeline
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	int		status;
	t_cmd	*current;
}	t_pipeline;

// Shell Structure
typedef struct s_shell
{
	t_env			*env;
	t_cmd			*cmds;
	t_token			*toks;
	int				exit_code;
	int				should_exit;
}	t_shell;

// ************************************************************************** //
//                                  PARSING                                   //
// ************************************************************************** //

// lexer.c - Main tokenization logic
t_token	*lexer(char *input);

// lexer_helpers.c - Token creation and character classification
t_token	*create_token(t_token_type type, char *value);
int		is_whitespace(char c);
int		is_special_char(char c);
int		is_fd_prefix(char c);
int		is_redir_char(char c);

// lexer_utils.c - Word extraction and escape detection
int		count_backslashes(char *str, int i);
char	*handle_word(char *input, int *i);

// lexer_quotes.c - Quote section copying with escape handling
void	copy_quoted_section(char *dst, char *src, int *dst_pos, int *src_pos);

// syntax_checker.c - Main syntax validation logic
int		check_syntax(void);

// syntax_checker_utils.c - Syntax checking helper functions
int		is_redir_token(t_token_type type);
void	print_syntax_error(t_token *token);

// parser.c - Main parsing logic and command building
void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd);
int		parser(void);

// parser_utils.c - Command parsing utilities
t_token	*parse_cmd(t_cmd *cmd, t_token *current);

// parser_split_mark.c - Mark tokens that need word splitting
void	mark_word_split(t_token *tokens);

// parser_heredoc_mark.c - Mark heredocs for expansion
void	mark_heredoc_expansion(t_token *tokens);

// parser_split_apply.c - Apply word splitting to marked tokens
void	apply_word_split(t_token **tokens);

// expander.c - Main token expansion logic
char	*expand_token(char *token);
void	expand_tokens(void);

// expander_quotes.c - Quote expansion (single, double, ANSI-C)
char	*expand_single_quotes(char *str, int *i);
char	*expand_double_quotes(char *str, int *i);
char	*expand_ansi_c_quotes(char *str, int *i);

// expander_substitutions.c - Variable and tilde substitution
char	*expand_tilde(char *str, int *i);
char	*expand_variable(char *str, int *i);

// expander_heredoc.c - Heredoc line expansion
char	*expand_heredoc_line(char *line);

// expander_utils.c - Expansion helper utilities
char	*dup_char_and_advance(char c, int *i);
char	*expand_var_from_name(char *var_name);
char	*append_string(char *result, char *to_add, int free_add);
char	*append_char(char *result, char c);

// quote_removal.c - Main quote removal logic
void	handle_quotes(void);

// quote_removal_utils.c - Quote removal utilities
int		count_unquoted_len(char *str);
void	copy_unquoted(char *dest, char *src);

// quote_removal_single.c - Single quote handling
void	copy_single_quoted(char *dest, char *src, int *j, int *i);

// quote_removal_double.c - Double quote handling with escape sequences
void	copy_double_quoted(char *dest, char *src, int *j, int *i);

// signals.c - Signal handling setup and handlers
void	setup_signals(int mode);

// free.c - Memory cleanup functions
void	free_tokens(t_token *tokens);
void	free_split(char **split);
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd *cmd_list);

// ************************************************************************** //
//                                 EXECUTION                                  //
// ************************************************************************** //

// libft_plus
int		ft_strcmp(char *s1, char *s2);
void	ft_itoa_buffer(int n, char *buffer);

// env_init.c
t_env	*init_env(char **envp);
void	env_add_back(t_env **env, t_env *new);

// env_set.c
void	env_set(t_env **env, char *key, char *value, int append);

// env_unset.c
void	env_unset(t_env **env, char *key);

// env_utils.c
char	*ft_getenv(t_env *env, char *key);
t_env	*env_find(t_env *env, char *key);
char	**env_to_array(t_env *env);

// env_shlvl.c
void	update_shlvl(void);

// free_env.c
void	free_env_nodes(t_env *env);
void	free_env_array(char **array);

// builtin_env.c
int		ft_env(void);

// builtin_export.c
int		ft_export(char **args);

// builtin_print_export.c
void	print_export(t_env *env);

// builtin_unset.c
int		ft_unset(char **args);

// builtin_cd.c
int		ft_cd(char **args);

// builtin_cd_utils.c
char	*cd_get_target(char **args, int *should_free, int *print_pwd);

// builtin_pwd.c
int		ft_pwd(void);

// builtin_echo.c
int		ft_echo(char **args);

// builtin_exit.c
int		ft_exit(char **args);

// exec_main.c
void	executor(void);
int		run_builtin(char **args);

// exec_paths.c
void	execve_with_path(t_cmd *cmd);

// exec_single.c
void	execute_single(t_cmd *cmd);

// exec_pipeline.c
void	execute_pipeline(t_cmd *cmd);

// exec_pipeline_utils.c
void	pipeline_child_exec(t_pipeline *p);
void	wait_all_pipeline(pid_t last_pid, t_pipeline *p);

// exec_redirect.c
int		apply_redirections(t_cmd *cmd);

// exec_utils.c
int		is_builtin(char *cmd);
void	save_fds(int saved_fds[3]);
void	restore_fds(int saved_fds[3]);
void	handle_child_status(int status);
int		handle_redirections(t_cmd *cmd);

// heredoc.c
int		prepare_heredocs(void);

// ************************************************************************** //
//                                   MAIN                                     //
// ************************************************************************** //

// main.c - Main entry point and shell initialization
t_shell	*shell(void);
void	cleanup_shell(void);

// main_utils.c - Input validation utilities
int		validate_input(char *input);

// main_pipeline.c - Command processing pipeline
void	process_and_execute(char *input);

// main_debug.c - Debug output functions
void	print_debug_info(void);
void	print_tokens(t_token *tokens, char *stage);
void	print_redirections(t_redir *redir);
void	print_cmd_list(t_cmd *cmd_list, char *stage);

// main_debug_utils.c - Debug helper utilities
void	print_tokens_copy(char *stage);

#endif