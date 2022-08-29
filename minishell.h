/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:24:18 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/29 13:48:24 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#	include <signal.h>
#	include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
//# include "~/.brew/opt/readline/include/readline"
//# include "../.brew/opt/readline/include/readline/readline.h"
//# include "../.brew/opt/readline/include/readline/rlstdc.h"
//# include "../.brew/opt/readline/include/readline/rlconf.h"

typedef enum	types
{
	WRD, 			//all words and characters
	W_SPACE, 	// \t and spaces
	PIPE, 		// pipes |
	S_QUOT, 	// ''
	D_QUOT, 	// ""
	DOLLA, 		// $
	O_TRNC, 	// >
	O_APEND,  // >>
	I_TRNC, 	// <
	I_APEND,  // <<
} t_types;

typedef struct s_env
{
	char	*sec;
	char	*value;
	struct s_env *next;
} t_env;

typedef struct token
{
	t_types type;
	char		*value;
	struct token *next;
} t_token;

typedef	struct cmd_detail
{
	t_types	typ;
	char		**cmd;
	char		*file;
	//maybe add a << stop char *
	struct s_cmd	*next;
} d_cmd;

typedef	struct valid_cmd
{
	d_cmd	*cmd;
	int		fd_in;
	int		fd_out;
	struct valid_cmd	*next;
} v_cmd;

typedef struct s_data
{
	char		**path;
	char		*line;
	char		**env;
	char		**args;
  char  	*w_path;
	char		**split;
	char		**cmd;
	char		*abs_path;
	char		*beg_line;
	char		*n_line;
	int			i_line;
	int			index;
	char		*var;
	char		*cd_path;
	int			check;
	int			i;
	int			j;
	int			chk_hrdoc; //this one is for heredoc to check so i can ignore expanding $PWD
	int			chk_dolla; //this one checks for $? so it print or not and change the value in how the process got end
	t_token	*node;
  t_token *trav;
	t_env		*shlvl_ptr;
	t_env		*var_exist;
	t_env		*l_env;
	//of derection
	t_token	*built_cmd;
	t_types	typ;
	//dial pipe
	t_token	*trav_p;
	//dial redirection
	t_token	*trav_r;
	t_token	*t_token;
	//parsing
	v_cmd		*valid_cmd;
	//d_cmd		*data_cmd;
	char		**split_cmd;

}	t_data;

/******* Function of tokenizer *********/
void	free_token_node(t_data *data);
void	add_dolla_begin(t_data *data);
void	add_dolla(t_data *data);
int		add_node(t_data *data, t_types typ);
int		ft_acceptable_char(int c);
void	is_quote_helper(t_data *data, int c, char *n_line);
void	ft_init_tokenizer(t_data *data, char *n_line, int i, t_types typ);
int		is_o_redirection(t_data *data, char *n_line);
int		is_i_redirection(t_data *data, char *n_line);
int		is_s_quote(t_data *data, char *n_line);
int		is_dolla(t_data *data, char *n_line);
int		is_d_quote(t_data *data, char *n_line);
void	tokenizer(t_data *data);

/******* Function of lexer ************/
int	lexer(t_data *data, t_types typ);

/******* Function of parser ************/
void  parser(t_data *data);




//i gotta sperate the function prototype
//**t_env *node_allocate(t_data *data);
//**void  export_cmd(t_data *data);
//**void  reinit_env(t_data *data);
//**void  echo_cmd(t_data *data);
//**void  env_cmd(t_data *data);
//**void  pwd_cmd(t_data *data);
//**void  get_env(t_data *data);
//**void  error(char *msg, int check);
//**void  lexer(t_data *data);
//**void  tokenizer(t_data *data);
//**void  unset_cmd(t_data *data);
void  nl(void);
//int		ft_acceptable_char(int c);

//**
void  token_s_quote(t_data *data);
//char  *grab_line(int fd);

#endif
