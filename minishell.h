/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:24:18 by hkaddour          #+#    #+#             */
/*   Updated: 2022/06/11 17:27:51 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
//# include "~/.brew/opt/readline/include/readline"
//# include "../.brew/opt/readline/include/readline/readline.h"
//# include "../.brew/opt/readline/include/readline/rlstdc.h"
//# include "../.brew/opt/readline/include/readline/rlconf.h"

typedef struct s_env
{
	char	*sec;
	char	*value;
	struct s_env *next;
} t_env;

typedef struct s_data
{
	char	**path;
	char	*line;
	char	**env;
	char	**args;
  char  *w_path;
	char	**split;
	char	**cmd;
	char	*abs_path;
}	t_data;

char  *grab_line(int fd);

#endif
