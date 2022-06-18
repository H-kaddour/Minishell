# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 11:07:05 by hkaddour          #+#    #+#              #
#    Updated: 2022/06/17 16:33:46 by hkaddour         ###   ########.fr        #
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
			parser.c \
			lexer.c
OBJS = $(SRC:.c=.o)
#move *.o to a build file
all: $(NAME)

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
	@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
