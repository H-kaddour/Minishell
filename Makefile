# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 11:07:05 by hkaddour          #+#    #+#              #
#    Updated: 2022/09/25 15:29:55 by hkaddour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
HEADER = minishell.h
FLAGS = -Wall -Wextra -Werror
#R_LINE = -L/usr/local/lib -I/usr/local/include -lreadline
#R_LINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -lreadline -L/usr/local/lib -I/usr/local/include
LIB = libft.a
READLINE = $(shell brew --prefix  readline)
OFILES = out_files
SRC = tokenizer/main.c \
			tokenizer/allocate_tokens.c \
			tokenizer/allocate_tokens_utils.c \
			tokenizer/tokenizer.c \
			tokenizer/tokenizer_helper.c \
			tokenizer/tokenizer_utils.c \
			tokenizer/lexer_pt1.c \
			tokenizer/lexer_pt2.c \
			tokenizer/parser.c \
			tokenizer/parser_utils.c \
			execution/execution.c \
			builtin_cmd/builtin_cmd.c \
			builtin_cmd/cd.c \
			builtin_cmd/env.c \
			builtin_cmd/pwd.c \
			builtin_cmd/echo.c \
			builtin_cmd/export.c \
			builtin_cmd/unset.c \
			builtin_cmd/exit.c

OBJS = $(SRC:.c=.o)
#move *.o to a build file
all: $(NAME)
#flag shows where the sigfault happen and force to check everything -fsanitize=address
$(NAME): $(LIB) $(OBJS)
	@$(CC) $(OBJS) $(LIB) -o $(NAME) -L $(READLINE)/lib -lreadline

$(OFILES)%/.o: %.c
	@mkdir -p $(@D)
	@$(CC) -I$(READLINE)/include -I./include $(HEADER) $(FLAGS) -o $@ -c $^

$(LIB):
	@make -C ./libft
	@mv libft/$(LIB) .

clean:
	@make clean -C ./libft
	@rm -rf *.o

fclean:
	@make fclean -C ./libft
	@rm -rf $(NAME) $(LIB) 
#@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
