/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:24:18 by hkaddour          #+#    #+#             */
/*   Updated: 2022/07/24 19:16:11 by hkaddour         ###   ########.fr       */
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
	char	*value;
	struct token *next;
} t_token;

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
}	t_data;

//void  sig_c(int c);
t_env *node_allocate(t_data *data);
void  export_cmd(t_data *data);
void  reinit_env(t_data *data);
void  echo_cmd(t_data *data);
void  env_cmd(t_data *data);
void  pwd_cmd(t_data *data);
void  get_env(t_data *data);
void  error(char *msg, int check);
void  lexer(t_data *data);
void  tokenizer(t_data *data);
void  unset_cmd(t_data *data);
//char  *grab_line(int fd);

#endif
