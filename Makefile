# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 11:07:05 by hkaddour          #+#    #+#              #
#    Updated: 2022/09/25 14:28:59 by hkaddour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
HEADER = minishell.h
FLAGS = -Wall -Wextra -Werror
#R_LINE = -L/usr/local/lib -I/usr/local/include -lreadline
#R_LINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -lreadline -L/usr/local/lib -I/usr/local/include
LIB = libft.a

SRC = main.c \
			allocate_tokens.c \
			allocate_tokens_utils.c \
			tokenizer.c \
			tokenizer_helper.c \
			tokenizer_utils.c \
			lexer_pt1.c \
			lexer_pt2.c \
			../tokenizer/parser.c \
			../tokenizer/parser_utils.c \
			../execution/execution.c \
			../builtin_cmd/builtin_cmd.c \
			../builtin_cmd/cd.c \
			../builtin_cmd/env.c \
			../builtin_cmd/pwd.c \
			../builtin_cmd/echo.c \
			../builtin_cmd/export.c \
			../builtin_cmd/unset.c \
			../builtin_cmd/exit.c

OBJS = $(SRC:.c=.o)
#move *.o to a build file
all: $(NAME)
#flag shows where the sigfault happen and force to check everything -fsanitize=address
$(NAME): $(LIB) $(OBJS)
	@$(CC) $(OBJS) $(LIB) -o $(NAME) -L ./readline/lib -lreadline

%.o: %.c
	@$(CC) -I ./readline/include -I $(HEADER) $(FLAGS) -c $^

$(LIB):
	@make -C ./libft
	@mv libft/$(LIB) .

clean:
	@rm -rf *.o

fclean:
	@rm -rf $(NAME) $(LIB) *.o
#@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
