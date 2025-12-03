#ifndef PARSING_H
# define PARSING_H

#include "../libft/includes/libft.h"

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

// Lexer Functions
t_token	*lexer(char *input);

// Lexer Helper Functions
int		is_whitespace(char c);
int		is_special_char(char c);
char	*extract_word(char *input, int *i);

// Parser Functions
t_cmd	*parser(t_token *tokens);

// Parser Helper Functions
t_token	*parse_single_cmd(t_cmd *cmd, t_token *current);
void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd);

// Free Functions
void	free_tokens(t_token *tokens);
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd *cmd_list);

#endif
