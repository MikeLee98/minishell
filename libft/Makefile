# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marioro2 <marioro2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/02 17:55:23 by mario             #+#    #+#              #
#    Updated: 2025/11/11 17:50:24 by marioro2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRC     = ft_atoi.c ft_bzero.c ft_calloc.c ft_get_next_line_utils.c ft_get_next_line.c \
          ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
          ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
          ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c \
          ft_memcpy.c ft_memmove.c ft_memset.c ft_printf_putchar.c ft_printf_puthex.c \
          ft_printf_putnbr.c ft_printf_putptr.c ft_printf_putstr.c ft_printf_putunsigned.c \
          ft_printf.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
          ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
          ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
          ft_strtrim.c ft_substr.c

OBJ     = $(SRC:.c=.o)
AR      = ar rcs

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
