# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akouame <akouame@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 11:07:05 by hkaddour          #+#    #+#              #
#    Updated: 2022/10/19 11:50:17 by akouame          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
HEADER = include/minishell.h
FLAGS = -Wall -Wextra -Werror
LIB = libft/libft.a
OFILE = ofiles
READLINE = $(shell brew --prefix  readline)
SRC = src/shell/main.c \
			src/shell/init.c \
			src/shell/prompt.c \
			src/shell/signals.c \
			src/shell/shell_utils.c \
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
			src/execution/exec_utils.c \
			src/builtin_cmd/builtin_cmd.c \
			src/builtin_cmd/cd/cd.c \
			src/builtin_cmd/cd/cd_everywhere.c \
			src/builtin_cmd/cd/cd_everywhere_helper.c \
			src/builtin_cmd/cd/cd_swaping_oldpwd_pwd.c \
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

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	mkdir $(OFILE)
	mv *.o $(OFILE)
	$(CC) $(OFILE)/* $(LIB) -o $(NAME) -L $(READLINE)/lib -lreadline

%.o: %.c
	$(CC) -I $(READLINE)/include -c $< -I $(HEADER)

$(LIB):
	make -C ./libft

clean:
	@make fclean -C ./libft
	@rm -rf $(OFILE)

fclean:
	@make fclean -C ./libft
	@rm -rf $(NAME) $(OFILE) *.dSYM

re: fclean all

.PHONY: all clean fclean re
