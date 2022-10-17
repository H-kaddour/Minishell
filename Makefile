# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 11:07:05 by hkaddour          #+#    #+#              #
#    Updated: 2022/10/17 11:37:21 by hkaddour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
HEADER = minishell.h
FLAGS = -Wall -Wextra -Werror
LIB = libft.a
READLINE = $(shell brew --prefix  readline)
OFILES = objdir
SRC = src/shell/main.c \
			src/shell/init.c \
			src/shell/prompt.c \
			src/shell/signals.c \
			src/shell/utils.c \
			src/tokenizer/tokenizer.c \
			src/tokenizer/tokenizer_helper.c \
			src/tokenizer/alloc_token/allocate_token_helper.c \
			src/tokenizer/alloc_token/allocate_tokens.c \
			src/tokenizer/alloc_token/allocate_tokens_dolla.c \
			src/tokenizer/alloc_token/allocate_tokens_dolla_begin.c \
			src/tokenizer/count_len_alloc/count_len_dolla.c \
			src/tokenizer/count_len_alloc/count_len_dolla_begin.c \
			src/tokenizer/count_len_alloc/count_value_len.c \
			src/tokenizer/count_len_alloc/count_value_len_helper.c \
			src/tokenizer/lexer/lexer_pt1.c \
			src/tokenizer/lexer/lexer_pt1_helper.c \
			src/tokenizer/lexer/lexer_pt2.c \
			src/tokenizer/token_identifier/token_identifier1.c \
			src/tokenizer/token_identifier/token_identifier2.c \
			src/tokenizer/token_identifier/token_identifier_helper.c \
			src/parser/heredoc/heredoc.c \
			src/parser/heredoc/heredoc_utils.c \
			src/parser/heredoc/len_hrdoc_data.c \
			src/parser/parser.c \
			src/parser/parser_helper.c \
			src/parser/parser_utils.c \
			src/execution/execution.c \
			src/execution/pipeline.c \
			src/execution/pipeline_helper.c \
			src/execution/redirection.c \
			src/execution/run_one_cmd.c \
			src/execution/utils.c \
			src/builtin_cmd/builtin_cmd.c \
			src/builtin_cmd/cd/cd.c \
			src/builtin_cmd/cd/cd_everywhere.c \
			src/builtin_cmd/cd/cd_everywhere_helper.c \
			src/builtin_cmd/cd/cd_swaping_oldpwd_pwd.c\ 
			src/builtin_cmd/echo.c \
			src/builtin_cmd/env/env.c \
			src/builtin_cmd/env/env_utils.c \
			src/builtin_cmd/env/get_env.c \
			src/builtin_cmd/exit/exit.c \
			src/builtin_cmd/exit/exit_utils.c \
			src/builtin_cmd/export/export.c \
			src/builtin_cmd/export/export_helper.c \
			src/builtin_cmd/export/export_utils.c \
			src/builtin_cmd/pwd.c \
			src/builtin_cmd/unset.c \
			src/free/free_collector.c \
			src/error/error_handling.c \
			src/builtin_cmd/builtin_utils.c

#../libft/libft.a
#-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -lreadline -L/usr/local/lib -I/usr/local/include -o minishell -g
OBJS = $(SRC:.c=.o)
#move *.o to a build file
all: $(NAME)
#flag shows where the sigfault happen and force to check everything -fsanitize=address
#$(NAME): $(LIB) $(OFILES) $(OBJS)
$(NAME): $(LIB) $(OBJS)
	$(CC) $(OBJS) $(LIB) -o $(NAME) -L $(READLINE)/lib -lreadline $(FLAGS)

#$(OBJFILES)/%.o: %.c
%.o: %.c
	$(CC) -I $(READLINE)/include -I ./include $(HEADER) -c $(OBJS) -g
#$(CC) -I $(READLINE)/include -I./include $(HEADER) $(FLAGS) -o $@ -c $^ -g

#$(OFILES):
#	@mkdir -p $(@)
	
$(LIB):
	@make -C ./libft
	@mv libft/$(LIB) .

clean:
	@make clean -C ./libft
	@rm -rf *.o

fclean:
	@make fclean -C ./libft
	@rm -rf $(NAME) $(LIB) $(OBJS) *.dSYM
#@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
