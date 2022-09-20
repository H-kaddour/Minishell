/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:01:19 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/20 12:43:17 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  size_cmd(t_data *data)
{
  data->size_cmd = 0;
  data->trav_cmd = data->v_cmd;
  while (data->trav_cmd)
  {
    data->size_cmd++;
    data->trav_cmd = data->trav_cmd->next;
  }
}

void  get_path(t_data *data)
{
  int i;
  char **sp;
  t_env *trav;
  char *cmd;

  i = 0;
  trav = data->l_env;
  while (ft_strcmp("PATH", trav->sec) && trav->next)
    trav = trav->next;
  if (!trav)
    return ;
  sp = ft_split(trav->value, ':');
  while (sp[i])
  {
    cmd = ft_strjoin(ft_strjoin(sp[i], "/"), data->v_cmd->cmd[0]);
    //if (access(ft_strjoin(ft_strjoin(sp[i], "/"), data->v_cmd->cmd[0]), F_OK) == 0)
    if (access(cmd, F_OK) == 0)
    {
      execve(cmd, data->v_cmd->cmd, data->env);
      free(cmd);
    }
    free(cmd);
    i++;
  }
  //here an error
  printf("minishell: command not found: %s\n", data->v_cmd->cmd[0]);
}

void  cmd_without_redirection(t_data *data)
{
  int pid; 

  pid = fork();
  //error here
  if (pid < 0)
    return ;
  if (pid == 0)
  {
    if (check_builtin(data->v_cmd->cmd[0]))
      exit(0);
    get_path(data);
    //exit(0);
  }
  if (pid >= 1)
  {
    wait(0);
    if (check_builtin(data->v_cmd->cmd[0]))
      builtin_cmd(data, data->v_cmd->cmd[0]);
    //check no need for 
    //and here if chk was 1 there's a error here cd or other cmd error
    //here check redirection
    return ;
  }
}

void  execution(t_data *data)
{
  //here loop for the parsing nodes and do four function one for single cmd and multiple cmd and redirection
  size_cmd(data);
  if (data->size_cmd == 1)
  {
    //here a fucntion to execute one cmd and check if it have redirection
      //execution normal
    if (!data->v_cmd->redirect)
    {
      //merge the cmd and redirection
      //printf("hey\n");
      //cat show alot of prompt
      cmd_without_redirection(data);
    }
    else
      return ;
      //execution with redirection
  }
  //else
  //{

  //}
  //printf("%d\n", data->size_cmd);
}
