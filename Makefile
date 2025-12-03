# **************************************************************************** #
#                              PROJECT SETTINGS                                #
# **************************************************************************** #

NAME = minishell
NAME_PARSING = minishell_parsing
NAME_EXECUTION = minishell_execution
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

SRC = $(shell find $(SRC_DIR) -name '*.c' -type f)
PARSING_SRC = $(shell find src/parsing/ -name '*.c' -type f)
EXECUTION_SRC = $(shell find src/execution/ -name '*.c' -type f)

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
PARSING_OBJ = $(patsubst src/parsing/%.c, $(OBJ_DIR)parsing/%.o, $(PARSING_SRC))
EXECUTION_OBJ = $(patsubst src/execution/%.c, $(OBJ_DIR)execution/%.o, $(EXECUTION_SRC))

# **************************************************************************** #
#                                 TARGETS                                      #
# **************************************************************************** #

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Building $(NAME)...$(RESET)"
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully created!$(RESET)"

v: $(NAME)
	@clear && valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
		--suppressions=readline.supp ./$(NAME)

p: parsing

parsing: $(LIBFT) $(NAME_PARSING)

$(NAME_PARSING): $(PARSING_OBJ)
	@echo "$(YELLOW)Building $(NAME_PARSING)...$(RESET)"
	@$(CC) $(PARSING_OBJ) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME_PARSING)
	@echo "$(GREEN)$(NAME_PARSING) successfully created!$(RESET)"

vp: parsing
	@clear && valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
		--suppressions=readline.supp ./$(NAME_PARSING)

# Execution target
e: execution

execution: $(LIBFT) $(NAME_EXECUTION)

$(NAME_EXECUTION): $(EXECUTION_OBJ)
	@echo "$(YELLOW)Building $(NAME_EXECUTION)...$(RESET)"
	@$(CC) $(EXECUTION_OBJ) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME_EXECUTION)
	@echo "$(GREEN)$(NAME_EXECUTION) successfully created!$(RESET)"

ve: execution
	@clear && valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
		--suppressions=readline.supp ./$(NAME_EXECUTION)

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

$(OBJ_DIR)parsing/%.o: src/parsing/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling (parsing): $<$(RESET)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/includes -c $< -o $@

$(OBJ_DIR)execution/%.o: src/execution/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling (execution): $<$(RESET)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/includes -c $< -o $@

# **************************************************************************** #
#                              CLEANING RULES                                  #
# **************************************************************************** #

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(RED)Object files have been cleaned! $(RESET)"; \
		echo "$(YELLOW)└── Removed directory: $(OBJ_DIR)$(RESET)"; \
	fi
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@if  [ -f "$(NAME)" ] || [ -f "$(NAME_PARSING)" ] || [ -f "$(NAME_EXECUTION)" ]; then \
		echo "$(RED)Everything has been cleaned!$(RESET)"; \
	fi
		@if [ -f "$(NAME)" ]; then \
		$(RM) $(NAME); \
		echo "$(YELLOW)└── Removed executable: $(NAME)$(RESET)"; \
	fi
	@if [ -f "$(NAME_PARSING)" ]; then \
		$(RM) $(NAME_PARSING); \
		echo "$(YELLOW)└── Removed executable: $(NAME_PARSING)$(RESET)"; \
	fi
	@if [ -f "$(NAME_EXECUTION)" ]; then \
		$(RM) $(NAME_EXECUTION); \
		echo "$(YELLOW)└── Removed executable: $(NAME_EXECUTION)$(RESET)"; \
	fi
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all p parsing e execution clean fclean re v vp ve 