# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 11:07:05 by hkaddour          #+#    #+#              #
#    Updated: 2022/06/11 18:36:49 by hkaddour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
HEADER = minishell.h
FLAGS = -Wall -Wextra -Werror
R_LINE = -L/usr/local/lib -I/usr/local/include -lreadline
LIB = libft.a
SRC = main.c
OBJS = $(SRC:.c=.o)
#move *.o to a build file
all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(OBJS) $(LIB) $(R_LINE) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $^ -I $(HEADER)

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
