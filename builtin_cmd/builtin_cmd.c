/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:54:38 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/22 17:16:33 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int  check_builtin(char *cmd)
{
  int   i;
  char  **sp;
  char  b_cmd[] = "cd echo pwd export unset env exit";

  i = 0;
  sp = ft_split(b_cmd, ' ');
  while (sp[i])
  {
    if (!ft_strcmp(sp[i], cmd))
      return (1);
    i++;
  }
  return (0);
}

void  builtin_cmd(t_data *data, char *cmd)
{
  if (!ft_strcmp(cmd, "cd"))
    cd_cmd(data);
  else if (!ft_strcmp(cmd, "echo"))
    echo_cmd(data);
  else if (!ft_strcmp(cmd, "pwd"))
    pwd_cmd(data);
  else if (!ft_strcmp(cmd, "env"))
    env_cmd(data);
  //else if (!ft_strcmp(cmd, "export"))
  //  export_cmd();
  //else if (!ft_strcmp(cmd, "unset"))
  //  unset_cmd();
  else if (!ft_strcmp(cmd, "exit"))
    exit_cmd(data);
}
