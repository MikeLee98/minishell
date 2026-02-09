# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 22:09:11 by migusant          #+#    #+#              #
#    Updated: 2026/02/06 15:16:07 by migusant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              PROJECT SETTINGS                                #
# **************************************************************************** #

NAME = minishell
LIBFT = libft/libft.a

# **************************************************************************** #
#                              COMPILER SETTINGS                               #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
RM = rm -f

# **************************************************************************** #
#                             DIRECTORY STRUCTURE                              #
# **************************************************************************** #

SRC_DIR = src/
OBJ_DIR = objects/
INC_DIR = includes/
LIBFT_DIR = libft/

# **************************************************************************** #
#                                  COLORS                                      #
# **************************************************************************** #

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

# **************************************************************************** #
#                              SOURCE FILES                                    #
# **************************************************************************** #

SRC = src/main.c \
	src/main_utils.c \
	src/main_pipeline.c \
	src/main_debug.c \
	src/main_debug_utils.c \
	src/parsing/lexer/lexer.c \
	src/parsing/lexer/lexer_helpers.c \
	src/parsing/lexer/lexer_checks.c \
	src/parsing/lexer/lexer_utils.c \
	src/parsing/lexer/lexer_quotes.c \
	src/parsing/syntax/syntax_checker.c \
	src/parsing/syntax/syntax_checker_utils.c \
	src/parsing/parser/parser.c \
	src/parsing/parser/parser_utils.c \
	src/parsing/parser/parser_split_mark.c \
	src/parsing/parser/parser_heredoc_mark.c \
	src/parsing/parser/parser_split_apply.c \
	src/parsing/expander/expander.c \
	src/parsing/expander/expander_quotes.c \
	src/parsing/expander/expander_substitutions.c \
	src/parsing/expander/expander_heredoc.c \
	src/parsing/expander/expander_utils.c \
	src/parsing/quotes/quote_removal.c \
	src/parsing/quotes/quote_removal_utils.c \
	src/parsing/quotes/quote_removal_single.c \
	src/parsing/quotes/quote_removal_double.c \
	src/parsing/signals/signals.c \
	src/parsing/free.c \
	src/execution/libft_plus/ft_itoa_heredoc.c \
	src/execution/libft_plus/ft_strcmp.c \
	src/execution/env/env_set.c \
	src/execution/env/env_init.c \
	src/execution/env/env_shlvl.c \
	src/execution/env/env_utils.c \
	src/execution/env/env_unset.c \
	src/execution/env/free_env.c \
	src/execution/builtins/builtin_cd.c \
	src/execution/builtins/builtin_cd_utils.c \
	src/execution/builtins/builtin_echo.c \
	src/execution/builtins/builtin_env.c \
	src/execution/builtins/builtin_exit.c \
	src/execution/builtins/builtin_export.c \
	src/execution/builtins/builtin_export_utils.c \
	src/execution/builtins/builtin_export_print.c \
	src/execution/builtins/builtin_pwd.c \
	src/execution/builtins/builtin_unset.c \
	src/execution/executor/exec_main.c \
	src/execution/executor/exec_single.c \
	src/execution/executor/exec_pipeline.c \
	src/execution/executor/exec_pipeline_utils.c \
	src/execution/executor/exec_redirect.c \
	src/execution/executor/exec_paths.c \
	src/execution/executor/exec_paths_utils.c \
	src/execution/executor/exec_utils.c \
	src/execution/executor/heredoc.c

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

# **************************************************************************** #
#                                 TARGETS                                      #
# **************************************************************************** #

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(YELLOW)Building $(NAME)...$(RESET)"
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully created!$(RESET)"

v: all
	@clear && valgrind --leak-check=full --show-leak-kinds=all \
		--track-fds=yes --trace-children=yes --track-origins=yes \
		--suppressions=valgrind.supp -s ./$(NAME)

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)

# **************************************************************************** #
#                            COMPILATION RULES                                 #
# **************************************************************************** #

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/includes -c $< -o $@

# **************************************************************************** #
#                              CLEANING RULES                                  #
# **************************************************************************** #

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(RED)Object files have been cleaned!$(RESET)"; \
		echo "$(YELLOW)└── Removed directory: $(OBJ_DIR)$(RESET)"; \
	fi
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(RED)Everything has been cleaned!$(RESET)"; \
		$(RM) $(NAME); \
		echo "$(YELLOW)└── Removed executable: $(NAME)$(RESET)"; \
	fi
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re v