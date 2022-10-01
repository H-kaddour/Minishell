/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:22:04 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/01 12:05:37 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *myown_getenv(t_data *data, char *sec, int *status)
{
  t_env *env;

  env = data->l_env;
  while (ft_strcmp(env->sec, sec) && env->next)
    env = env->next;
  if (!ft_strcmp(env->sec, sec))
  {
    if (status)
      *(status) = 1;
    return (ft_strdup(env->value));
  }
  else
  {
    if (status)
      *(status) = 0;
    return (0);
  }
}

void  error_cd(t_data *data, char *msg)
{
  data->chk_dolla = 1;
  printf("%s\n", msg);
}

void  old_pwd_alloc(t_data *data)
{
  t_env *node;
  t_env *trav;

  trav = data->l_env;
  node = node_allocate();
  node->sec = ft_strdup("OLDPWD");
  while (trav->next)
    trav = trav->next;
  trav->next = node;
  data->old_pwd_make = 1;
}

int get_home_path(t_data *data, t_env **trav_e, char *cmd)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, "HOME") && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, "HOME"))
  {
    *trav_e = trav;
    return (0);
  }
  else
  {
    printf("minishell: cd: HOME not set\n");
    return (1);
  }
}

void  get_pwd(t_data *data, char *path)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, "PWD") && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, "PWD"))
  {
    data->old_pwd_value = ft_strdup(trav->value);
    if (!ft_strcmp(trav->value, path))
      return ;
    else
    {
      trav->value = ft_strdup(path);
      data->pwd_of_mysys = ft_strdup(path);
    }
  }
  else
  {
    data->old_pwd_value = data->pwd_of_mysys;
    data->pwd_of_mysys = ft_strdup(path);
  }
}

char  *alloc_old_pwd(t_data *data)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, "PWD") && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, "PWD"))
  {
    return (ft_strdup(trav->value));
  }
  return (ft_strdup(data->pwd_of_mysys));
}

void  get_old_pwd(t_data *data, int chk)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, "OLDPWD") && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, "OLDPWD"))
  {
    if (data->old_pwd_value)
    {
      if (chk == 0)
        trav->value = data->old_pwd_value;
      else
        trav->value = alloc_old_pwd(data);
    }
  }
}

void  execute_cmd_cd(t_data *data, char *cmd, char *path)
{
  if (chdir(path) != 0)
  {
    data->chk_dolla = 1;
    printf("minishell: cd: %s: No such file or directory\n", cmd);
    return ;
  }
  if (data->old_pwd_make == 0)
    old_pwd_alloc(data);
  get_pwd(data, path);
  get_old_pwd(data, 0);
  data->chk_dolla = 0;
}

int slash_loop(char *cmd)
{
  if (!cmd)
    return (1);
  while (*cmd == '/' && *cmd)
    cmd++;
  if (*cmd == 0)
    return (1);
  return (0);
}

void  cd_home_path(t_data *data, char *cmd)
{
  int i;
  int j;
  int lst;
  char *path;
  t_env *trav_e;

  i = 1;
  if (cmd)
  {
    if (cmd[0] == '~' && slash_loop(&cmd[1]))
    {
      if (!getenv("HOME"))
      {
        printf("minishell: cd: HOME not set\n");
        return ;
      }
      execute_cmd_cd(data, cmd, getenv("HOME"));
      return ;
    }
  }
  if (get_home_path(data, &trav_e, cmd))
    return ;
  if (!cmd)
  {
    execute_cmd_cd(data, cmd, trav_e->value);
    return ;
  }
  else
  {
    if (cmd[i] == 0)
    {
      execute_cmd_cd(data, cmd, trav_e->value);
      return ;
    }
    else
    {
      if (cmd[i] == '/')
      {
        while (cmd[i] == '/')
          i++;
        if (cmd[i] == 0)
        {
          execute_cmd_cd(data, cmd, trav_e->value);
          return ;
        }
        else
        {
          lst = ft_strlen(cmd) - 1;
          if (cmd[lst] != '/')
            lst += 1;
          while (cmd[lst - 1] == '/')
            lst--;
          path = malloc(sizeof(char) * (lst - i) + 1);
          j = 0;
          while (&cmd[i] != &cmd[lst])
            path[j++] = cmd[i++];
          path[j] = 0;
        }
        path = ft_strjoin(trav_e->value, ft_strjoin("/", path));
        execute_cmd_cd(data, cmd, path);
      }
      else
        printf("minishell: cd: %s: No such file or directory\n", cmd);
    }
  }
}

void  execute_cd_swap_old_pwd(t_data *data)
{
  t_env *trav_pwd;
  t_env *trav_o_p;
  char  *val;

  trav_pwd = data->l_env;
  trav_o_p = data->l_env;
  while (ft_strcmp(trav_pwd->sec, "PWD") && trav_pwd->next)
    trav_pwd = trav_pwd->next;
  while (ft_strcmp(trav_o_p->sec, "OLDPWD") && trav_o_p->next)
    trav_o_p = trav_o_p->next;
  if (ft_strcmp(trav_o_p->sec, "OLDPWD"))
  {
    data->chk_dolla = 1;
    printf("minishell: cd: OLDPWD not set\n");
    return ;
  }

  val = trav_o_p->value;
  if (!ft_strcmp(trav_pwd->sec, "PWD"))
  {
    trav_o_p->value = ft_strdup(trav_pwd->value);
    trav_pwd->value = ft_strdup(val);
    data->pwd_of_mysys = ft_strdup(val);
  }
  else
  {
    trav_o_p->value = ft_strdup(data->pwd_of_mysys);
    data->pwd_of_mysys = ft_strdup(val);
  }
  if (chdir(val) != 0)
  {
    data->chk_dolla = 1;
    printf("minishell: cd: %s: No such file or directory\n", trav_pwd->value);
    return ;
  }
  data->chk_dolla = 0;
}

int check_old_pwd(t_data *data)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, "OLDPWD") && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, "OLDPWD"))
    return (0);
  else
    return (1);
}

void  cd_between_pwd_and_oldpwd(t_data *data, char *cmd)
{
  int i;

  i = 0;
  if (cmd[1] != 0)
  {
    printf("minishell: cd: -: invalid option\n");
    return ;
  }
  else
  {
    if (check_old_pwd(data))
    {
      printf("minishell: cd: OLDPWD not set\n");
      return ;
    }
    else
    {
      execute_cd_swap_old_pwd(data);
      pwd_cmd(data);
    }
  }
}

//int len_for_root(char *start, char *end)
//{
//  if (&start[0] == &end[0])
//    return (1);
//  else
//    return (0);
//}

int check_errors(char *cmd)
{
  int i;

  i = 0;
  while (cmd[i])
  {
    if (cmd[i] == '.')
    {
      if (ft_strcmp(cmd, "..") && ft_strcmp(cmd, "."))
        return (1);
      else
      {
        if (!ft_strcmp(cmd, ".."))
          i += 2;
        else if (!ft_strcmp(cmd, "."))
          i++;
      }
    }
    if (cmd[i] == '/')
      i++;
    i++;
  }
  return (0);
}

void  cd_double_dot(t_data *data, char *cmd)
{
  int   i;
  int   len;
  char  *pwd;
  char  *path;

  i = 0;
  if (chdir(cmd) != 0)
  {
    printf("minishell: cd: %s: No such file or directory\n", cmd);
    return ;
  }
  pwd = malloc(sizeof(char) * 1024);
  getcwd(pwd, 1024);
  printf("%s\n", pwd);
  //pwd = myown_getenv(data, "PWD", 0);
  //if (!pwd)
  //  pwd = data->pwd_of_mysys;
  //if (check_errors(cmd))
  //{
  //  printf("minishell: cd: %s: No such file or directory\n", cmd);
  //  return ;
  //  //error here
  //}
  //path = take_off_the_lst_slash(cmd);
  
  //if (path[0] == '/')
  //{
  //  while (path[i])
  //}
  //else
  //here check if / or not

}

//void  cd_double_dot(t_data *data, char *cmd)
//{
//  int   i;
//  int   lst;
//  t_env *trav;
//  char  *path;
//  char  *val;
//
//  trav = data->l_env;
//  while (ft_strcmp(trav->sec, "PWD") && trav->next)
//    trav = trav->next;
//  if (1)
//  {
//    if (!ft_strcmp(trav->sec, "PWD"))
//      val = trav->value;
//    else
//      val = data->pwd_of_mysys;
//    lst = ft_strlen(val) - 1;
//    while (val[lst] != '/')
//      lst--;
//    if (len_for_root(&val[0], &val[lst]) == 1)
//    {
//      execute_cmd_cd(data, cmd, "/");
//      return ;
//    }
//    path = malloc(sizeof(char) * lst);
//    i = 0;
//    while (&val[i] != &val[lst])
//    {
//      path[i] = val[i];
//      i++;
//    }
//    path[i] = 0;
//    execute_cmd_cd(data, cmd, path);
//  }
//}

int cd_to_root(t_data *data, char *cmd)
{
  int i;

  i = 0;
  while (cmd[i] == '/' && cmd[i])
    i++;
  if (cmd[i] != 0)
    return (0);
  else
  {
    execute_cmd_cd(data, cmd, "/");
    return (1);
  }
}

char *take_off_the_lst_slash(char *cmd)
{
  char  *path;
  int   lst;
  int   i;

  i = 0;
  lst = ft_strlen(cmd) - 1;
  if (cmd[lst] != '/')
    lst++;
  while (cmd[lst - 1] == '/')
    lst--;
  i = 0;
  path = malloc(sizeof(char) * lst);
  while (&cmd[i] != &cmd[lst])
  {
    path[i] = cmd[i];
    i++;
  }
  path[i] = 0;
  return (path);
}

void  cd_path_and_folders(t_data *data, char *cmd)
{
  t_env *trav;
  char  *path;

  trav = data->l_env;
  if (cmd[0] == '/')
  {
    if (cd_to_root(data, cmd))
      return ;
    path = take_off_the_lst_slash(cmd);
    execute_cmd_cd(data, cmd, path);
  }
  else
  {
    while (ft_strcmp(trav->sec, "PWD") && trav->next)
      trav = trav->next;
    if (1)
    {
      path = take_off_the_lst_slash(cmd);
      if (!ft_strcmp(trav->sec, "PWD"))
      {
        if (trav->value[1] == 0)
          path = ft_strjoin(trav->value, path);
        else
          path = ft_strjoin(trav->value, ft_strjoin("/", path));
      }
      else
      {
        if (data->pwd_of_mysys[1] == '/')
          path = ft_strjoin(data->pwd_of_mysys, path);
        else
          path = ft_strjoin(data->pwd_of_mysys, ft_strjoin("/", path));
      }
      execute_cmd_cd(data, cmd, path);
    }
  }
}

int check_if_pwd_exist(t_data *data)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, "PWD") && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, "PWD"))
    return (1);
  return (0);
}

void  cd_period(t_data *data)
{
  if (data->old_pwd_make == 0)
    old_pwd_alloc(data);
  get_old_pwd(data, 1);
  if (chdir(alloc_old_pwd(data)))
  {
    error_cd(data, "minishell: cd: No such file or directory");
    return ;
  }
  data->chk_dolla = 0;
  return ;
}

void  cd_cmd(t_data *data)
{
  t_cmd *trav_c;
  trav_c = data->v_cmd;

  //if (!trav_c->cmd[1] || trav_c->cmd[1][0] == '~' || !trav_c->cmd[1][0])
  //  cd_home_path(data, trav_c->cmd[1]);
  //else if (!ft_strcmp(trav_c->cmd[1], "."))
  //{
  //  cd_period(data);
  //  return ;
  //}
  //else if (trav_c->cmd[1][0] == '-')
  //  cd_between_pwd_and_oldpwd(data, trav_c->cmd[1]);
  //else if (!ft_strncmp(trav_c->cmd[1], "..", 2))
    cd_double_dot(data, trav_c->cmd[1]);
  //else if (trav_c->cmd[1][0] != '-' && trav_c->cmd[1][0] != '~' && trav_c->cmd[1][0] != '.' && trav_c->cmd[1])
  //  cd_path_and_folders(data, trav_c->cmd[1]);
  //else
  //{
  //  data->chk_dolla = 1;
  //  printf("minishell: cd: %s: No such file or directory\n", trav_c->cmd[1]);
  //}
}

//now i will add .. and . and path and / in one function it runs and then i get the path\
//with getcwd and put it in env
//then check all possible way of cd
//and gad norminette 
//and start in * in parsing 
//and free leaks
//and after malloc put bzero in the address
//in tokenizer count len of malloc
