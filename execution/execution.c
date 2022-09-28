/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:01:19 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/28 15:21:17 by hkaddour         ###   ########.fr       */
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

int find_slash(char *cmd)
{
  int i;

  i = 0;
  while (cmd[i])
  {
    if (cmd[i] == '/')
      return (1);
    i++;
  }
  return (0);
}

void  exec_file(t_data *data, t_cmd *cmd)
{
  char *exec;

  if (find_slash(*cmd->cmd))
  {
    exec = *cmd->cmd;
    if (access(exec, F_OK) == 0)
    {
      if (access(exec, X_OK) == 0)
        execve(exec, cmd->cmd, env_double_ptr(data));
      else
      {
         printf("minishell: %s: Permission denied\n", exec);
         exit(126);
      }
    }
    printf("minishell: %s: command not found\n", cmd->cmd[0]);
    exit(127);
  }
}

void  exec_cmd_path(t_data *data, t_cmd *cmd, char **sp)
{
  int   i;
  char  *path;

  i = 0;
  while (sp[i])
  {
    path = ft_strjoin(ft_strjoin(sp[i], "/"), cmd->cmd[0]);
    if (access(path, F_OK) == 0)
    {
      if (access(path, X_OK) == 0)
      {
        execve(path, cmd->cmd, env_double_ptr(data));
        free(path);
      }
      else
      {
         printf("minishell: %s: Permission denied\n", path);
         exit(126);
      }
    }
    free(path);
    i++;
  }
  printf("minishell: %s: command not found\n", cmd->cmd[0]);
  exit(127);
}

void  execute_sys_cmd(t_data *data, t_cmd *cmd)
{
  int i;
  char **sp;
  char *env;

  i = 0;
  exec_file(data, cmd);
  env = myown_getenv(data, "PATH", 0);
  if (!env)
  {
    data->chk_dolla = 1;
    printf("TERM environment variable not set.");
  }
  sp = ft_split(env, ':');
  exec_cmd_path(data, cmd, sp);
}

void  error_execution(t_data *data, char *msg)
{
  data->chk_dolla = 1;
  printf("%s\n", msg);
  exit(2);
}

void  child_process_run_one_cmd(t_data *data)
{
  if (check_builtin(&data->v_cmd->cmd[0]))
    exit(0);
  if (data->chk_redct_exist == 1)
  {
    dup2(data->v_cmd->f_in, STDIN_FILENO);
    dup2(data->v_cmd->f_out, STDOUT_FILENO);
  }
  execute_sys_cmd(data, data->v_cmd);
}

void  exit_status(int *exit_stat, int status)
{
  if (status == 256)
    *exit_stat = 1;
  else if (status == 32256)
    *exit_stat = 126;
  else if (status == 32512)
    *exit_stat = 127;
  else
    *exit_stat = 0;
}

void  run_one_cmd(t_data *data)
{
  int pid; 
  int status;

  pid = fork();
  if (pid < 0)
    error_execution(data, "minishell: fork: error\n");
  if (pid == 0)
  {
    if (data->v_cmd->cmd[0])
      child_process_run_one_cmd(data);
  }
  if (pid >= 1)
  {
		signal(SIGINT, SIG_IGN);
    waitpid(pid, &status, 0);
    exit_status(&data->chk_dolla, status);
    if (data->v_cmd->cmd[0])
    {
      if (check_builtin(&data->v_cmd->cmd[0]))
        builtin_cmd(data, data->v_cmd->cmd[0]);
    }
    return ;
  }
}

void  fds_closer(t_cmd *cmd, t_red *red)
{
   if (red->typ == O_TRNC || red->typ == O_APEND)
   {
     if (cmd->f_out > 1)
       close(cmd->f_out);
   }
   else if (red->typ == I_TRNC)
   {
     if (cmd->f_in > 0)
       close(cmd->f_in);
   }
}

int red_o_trnc(t_data *data, t_red *red, t_cmd *cmd, int *fd)
{
  if (access(red->file, F_OK) == 0)
  {
    if (access(red->file, W_OK) == 0)
      *fd = open(red->file, O_WRONLY | O_TRUNC);
    else
    {
      data->chk_dolla = 126;
      printf("minishell: %s: Permission denied\n", red->file);
      return (1);
    }
  }
  *fd = open(red->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  cmd->f_out = *fd;
  return (0);
}

int red_o_apend(t_data *data, t_red *red, t_cmd *cmd, int *fd)
{
  if (access(red->file, F_OK) == 0)
  {
    if (access(red->file, W_OK) == 0)
      *fd = open(red->file, O_WRONLY | O_APPEND);
    else
    {
      data->chk_dolla = 126;
      printf("minishell: %s: Permission denied\n", red->file);
      return (1);
    }
  }
  else
    *fd = open(red->file, O_RDWR | O_APPEND | O_CREAT, 0644);
  cmd->f_out = *fd;
  return (0);
}

int red_i_trnc(t_data *data, t_red *red, t_cmd *cmd, int *fd)
{
  if (access(red->file, F_OK) == 0)
  {
    if (access(red->file, R_OK) == 0)
      *fd = open(red->file, O_RDONLY);
    else
    {
      data->chk_dolla = 126;
      printf("minishell: %s: Permission denied\n", red->file);
      return (1);
    }
  }
  else
  {
    data->chk_dolla = 1;
    printf("minishell: %s: No such file or directory\n", red->file);
    return (1);
  }
  cmd->f_in = *fd;
  return (0);
}

int redirection_changer(t_data *data, t_red *red, t_cmd *cmd, int *fd)
{
  if (red->typ == O_TRNC)
  {
    if (red_o_trnc(data, red, cmd, fd))
      return (1);
  }
  else if (red->typ == O_APEND)
  {
    if (red_o_apend(data, red, cmd, fd))
      return (1);
  }
  else if (red->typ == I_TRNC)
  {
    if (red_i_trnc(data, red, cmd, fd))
      return (1);
  }
  return (0);
}

int check_redirection(t_data *data, t_cmd *cmd)
{
  t_red *trav;
  int i;
  int fd;

  i = 0;
  trav = cmd->redirect;
  if (trav)
  {
    data->chk_redct_exist = 1;
    while (trav)
    {
      if (i > 0)
        fds_closer(cmd, trav);
      if (redirection_changer(data, trav, cmd, &fd))
        return (1);
      else if (trav->typ == I_APEND)
        cmd->f_in = data->hrdoc_fd[0];
      trav = trav->next;
      i++;
    }
  }
  return (0);
}

void  execution(t_data *data)
{
  size_cmd(data);
  if (data->size_cmd == 1)
  {
    if (!check_redirection(data, data->v_cmd))
      run_one_cmd(data);
    if (data->chk_redct_exist == 1)
    {
      if (data->v_cmd->f_in > 0)
        close(data->v_cmd->f_in);
      if (data->v_cmd->f_out > 1)
        close(data->v_cmd->f_out);
    }
  }
  //else
  //  pipeline(data);
}
