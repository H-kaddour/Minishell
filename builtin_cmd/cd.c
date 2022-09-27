/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:22:04 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/27 15:42:21 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//pseudo code
//always check chdir
//cd
//cd path
//cd directory
//cd directory/ it the last char /
//cd some some some
//cd ~
//cd ~/ and ~///
//cd - change between oldpath and cd -- reset old path with his the current pwd
//cd / ////////  same and it's pwd /
//cd .. more than that error
//cd .
//when u remove a 
//always change pwd and oldpath new path in env 

char *myown_getenv(t_data *data, char *sec, int *status)
{
  t_env *env;

  env = data->l_env;
  while (ft_strcmp(env->sec, sec) && env->next)
    env = env->next;
  if (!ft_strcmp(env->sec, sec))
  {
    *(status) = 1;
    return (ft_strdup(env->value));
  }
  else
  {
    *(status) = 0;
    return (0);
  }
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
  //if (!cmd)
  //{
  while (ft_strcmp(trav->sec, "HOME") && trav->next)
    trav = trav->next;
  //if (!ft_strcmp(trav->sec, "HOME") && trav->next)
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
  //here if i didn't find it 
  //}
  //else
  //  return (0);
}

void  get_pwd(t_data *data, char *path)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, "PWD") && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, "PWD"))
  {
    //clean it's value in env to be empty
    data->old_pwd_value = ft_strdup(trav->value);
    if (!ft_strcmp(trav->value, path))
      return ;
    else
    {
      //free(trav->value);
      trav->value = ft_strdup(path);
      data->pwd_of_mysys = ft_strdup(path);
      //data->pwd_of_mysys = trav->value;
    }
  }
  else
  {
    data->old_pwd_value = data->pwd_of_mysys;
    //if (!data->pwd_of_mysys && data->chk_o_p_sys == 0)
    //{
    //  data->old_pwd_value = getenv("PWD");
    //  data->chk_o_p_sys = 1;
    //}
    //else
    //  data->old_pwd_value = data->pwd_of_mysys;
    data->pwd_of_mysys = ft_strdup(path);
  }
  //here if didn't find it
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
  //error here else
  //else if (ft_strcmp(trav->sec, "PWD") && !data->pwd_of_mysys)
  //  return (ft_strdup(getenv("PWD")));
  return (ft_strdup(data->pwd_of_mysys));
  //return (ft_strdup(getenv("PWD")));
  //return (ft_strdup(trav->value));
}

void  get_old_pwd(t_data *data, int chk)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, "OLDPWD") && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, "OLDPWD"))
  {
    //if (data->old_pwd_value[0] != 0)
    //{
    //  if (!ft_strcmp(trav->value, data->old_pwd_value))
    //    return ;
    //}
    //else
    if (data->old_pwd_value)
    {
      if (chk == 0)
      {
        //if (trav->value)
        //  free(trav->value);
        trav->value = data->old_pwd_value;
      }
      else
      {
        //if (trav->value)
        //  free(trav->value);
        trav->value = alloc_old_pwd(data);
      }
      //if (trav->value[0] != 0)
      //  free(trav->value);
      //trav->value = data->old_pwd_value;
    }
    //i added this one and this bitch give me the problem
    //if (chdir(trav->value) != 0)
    //{
    //  printf("minishell: cd: No such file or directory\n");
    //  return ;
    //}
  }
  //else
  //{
  //  printf("minishell: cd: OLDPWD not set\n");
  //  return ;
  //}
}

//int check_if_home_only(char *cmd)
//{
//  while (*cmd)
//  {
//    if (*cmd != '~' && *cmd != '/')
//      return (0);
//    cmd++;
//  }
//  return (1);
//}

void  execute_cmd_cd(t_data *data, char *cmd, char *path)
{
  //if (cmd)
  //{
  //  //if (cmd[0] == '~')
  //  if (cmd[0] != '/')
  //  {
  //    if (check_if_home_only(cmd))
  //      path = getenv("HOME");
  //  }
  //  //else if (check_if_home_only(cmd))
  //  //  path = getenv("HOME");
  //}
  if (chdir(path) != 0)
  {
    //it should print the cmd not the path
    //printf("minishell: cd: %s: No such file or directory\n", path);
    data->chk_dolla = 1;
    printf("minishell: cd: %s: No such file or directory\n", cmd);
    return ;
  }
  //maybe i should sort the env
  if (data->old_pwd_make == 0)
    old_pwd_alloc(data);
  get_pwd(data, path);
  get_old_pwd(data, 0);
  data->chk_dolla = 0;
  //prompt_changer(data);
  //here add the path to pwd and oldpath and change the prompt path
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

//here just send cmd what it point to the one index
void  cd_home_path(t_data *data, char *cmd)
{
  int i;
  int j;
  int lst;
  char *path;
  t_env *trav_e;

  i = 1;
  //if (cmd)
  //{
  //  if (cmd[0] == '~' && !slash_loop(&cmd[1]))
  //  {
  //    if (get_home_path(data, &trav_e, cmd))
  //      return ;
  //  }
  //  else
  //    execute_cmd_cd(data, cmd, getenv("HOME"));
  //    //trav_e->value = getenv("HOME");
  //}
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
  //pass ~ direct to /
  if (!cmd)
  {
    execute_cmd_cd(data, cmd, trav_e->value);
    return ;
    //send it to execution and changing path and all that
  }
  else
  {
    if (cmd[i] == 0)
    {
      execute_cmd_cd(data, cmd, trav_e->value);
      return ;
      //execution direct
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
          //lst = ft_strlen(&cmd[i]) - 1;
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
        //path = ft_strjoin(trav_e->value, path);
        path = ft_strjoin(trav_e->value, ft_strjoin("/", path));
        execute_cmd_cd(data, cmd, path);
      }
      else
      {
        printf("minishell: cd: %s: No such file or directory\n", cmd);
        //error
      }
    }
  }
}

void  execute_cd_swap_old_pwd(t_data *data)
{
  t_env *trav_pwd;
  t_env *trav_o_p;
  char  *path;
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
  //trav_o_p->value = ft_strdup(trav_pwd->value);
  if (!ft_strcmp(trav_pwd->sec, "PWD"))
  {
    trav_o_p->value = ft_strdup(trav_pwd->value);
    trav_pwd->value = ft_strdup(val);
    data->pwd_of_mysys = ft_strdup(val);
    //val = ft_strdup(trav_pwd->value);
    //trav_pwd->value = trav_o_p->value;
  }
  else
  {
    trav_o_p->value = ft_strdup(data->pwd_of_mysys);
    data->pwd_of_mysys = ft_strdup(val);
    //val = ft_strdup(data->pwd_of_mysys);
    //data->pwd_of_mysys = trav_o_p->value;
  }
  //path = val;
  //val = trav_o_p->value;
  //**trav_o_p->value = val;
  //else
  //{
  //  data->chk_dolla = 1;
  //  printf("minishell: cd: PWD not set\n");
  //  return ;
  //}
  //if (!ft_strcmp(trav_o_p->sec, "OLDPWD"))
  //{
  //  trav_o_p->value = path;
  //}
  //else
  //{
  //  data->chk_dolla = 1;
  //  printf("minishell: cd: OLDPWD not set\n");
  //  return ;
  //}
  //check error if OLDPWD if does not exist
  //if (chdir(trav_pwd->value) != 0)
  //**if (chdir(val) != 0)
  if (chdir(val) != 0)
  {
    data->chk_dolla = 1;
    printf("minishell: cd: %s: No such file or directory\n", trav_pwd->value);
    return ;
  }
  data->chk_dolla = 0;
  //prompt_changer(data);
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
    //means it's not exist yet
    //if (data->old_pwd_make == 0)
    if (check_old_pwd(data))
    {
      //data->old_pwd_make = 0;
      printf("minishell: cd: OLDPWD not set\n");
      return ;
    }
    else
    {
      //swap the value of pwd and oldpwd and print the pwd execute
      execute_cd_swap_old_pwd(data);
      pwd_cmd(data);
    }
  }
}

int len_for_root(char *start, char *end)
{
  if (&start[0] == &end[0])
    return (1);
  else
    return (0);
}

void  cd_double_dot(t_data *data, char *cmd)
{
  int   i;
  int   lst;
  t_env *trav;
  char  *path;
  char  *val;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, "PWD") && trav->next)
    trav = trav->next;
  //if (!ft_strcmp(trav->sec, "PWD") && trav->next)
  if (1)
  {
    if (!ft_strcmp(trav->sec, "PWD"))
      val = trav->value;
    //else if (ft_strcmp(trav->sec, "PWD") && !data->pwd_of_mysys)
    //  val = getenv("PWD");
    else
      val = data->pwd_of_mysys;
    //path = trav->value;
    lst = ft_strlen(val) - 1;
    //here send it to exection direct cuz it's the root /
    //this one blash
    //if (trav->value[lst] == '/')
    //{
    //  execute_cmd_cd(data, "/");
    //  return ;
    //}
    while (val[lst] != '/')
      lst--;
    //means / root
    //if (ft_strlen(trav->value[lst]) == 1)
    //len_for_root(&trav->value[0], &trav->value[lst]);
    //if (trav->value[lst] == '/')
    if (len_for_root(&val[0], &val[lst]) == 1)
    {
      execute_cmd_cd(data, cmd, "/");
      return ;
    }
    path = malloc(sizeof(char) * lst);
    i = 0;
    while (&val[i] != &val[lst])
    {
      path[i] = val[i];
      i++;
    }
    path[i] = 0;
    execute_cmd_cd(data, cmd, path);
  }
  //else
  //{
  //  data->chk_dolla = 1;
  //  printf("minishell: cd: PWD not set\n");
  //  return ;
  //}
  //error here
}

int cd_to_root(t_data *data, char *cmd)
{
  int i;

  i = 0;
  while (cmd[i] == '/' && cmd[i])
    i++;
  if (cmd[i] != 0)
    return (0);
  //{
  //  printf("minishell: cd: %s: No such file or directory\n", cmd);
  //  return ;
  //}
  else
  {
    execute_cmd_cd(data, cmd, "/");
    return (1);
  }
}

//pseudo code:
//"/path/path"
//"/path/path/"
//"/"
//"tmp/"
//"tmp"

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
  //int   lst;
  //int   i;
  char  *path;

  //lst = 0;
  trav = data->l_env;
  if (cmd[0] == '/')
  {
    //if (cmd[1] == 0)
    if (cd_to_root(data, cmd))
      return ;
    //{
    //  execute_cmd_cd(data, "/");
    //  return ;
    //}
    //**lst = ft_strlen(cmd) - 1;
    //**if (cmd[lst] != '/')
    //**  lst++;
    //**while (cmd[lst - 1] == '/')
    //**  lst--;
    //**i = 0;
    //**path = malloc(sizeof(char) * lst);
    //**while (&cmd[i] != &cmd[lst])
    //**{
    //**  path[i] = cmd[i];
    //**  i++;
    //**}
    //**path[i] = 0;
    path = take_off_the_lst_slash(cmd);
    execute_cmd_cd(data, cmd, path);
  }
  else
  {
    //this one make a function that get u pwd
    while (ft_strcmp(trav->sec, "PWD") && trav->next)
      trav = trav->next;
    //if (!ft_strcmp(trav->sec, "PWD") || data->pwd_of_mysys)
    if (1)
    {
      path = take_off_the_lst_slash(cmd);
      //what if pwd equal 1 and that one it's not / it's * or somth
      if (!ft_strcmp(trav->sec, "PWD"))
      {
        //baghi nefhm hadi ******
        //means ila kan pwd root /
        if (trav->value[1] == 0)
          path = ft_strjoin(trav->value, path);
        else
          path = ft_strjoin(trav->value, ft_strjoin("/", path));
      }
      else
      {
        //if (!data->pwd_of_mysys)
        //  data->pwd_of_mysys = getenv("PWD");
        if (data->pwd_of_mysys[1] == '/')
          path = ft_strjoin(data->pwd_of_mysys, path);
        else
          path = ft_strjoin(data->pwd_of_mysys, ft_strjoin("/", path));
      }
      execute_cmd_cd(data, cmd, path);
    }
    //else an error msg if we take the env down
    //else
    //{
    //  //data->chk_dolla = 1;
    //  //printf("minishell: cd: PWD not set\n");

    //  return ;
    //}
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
  //data->chk_dolla = 1;
  //printf("minishell: cd: OLDPWD not set\n");
  return (0);
}

void  cd_cmd(t_data *data)
{
  //char  *path;
  t_cmd *trav_c;
  trav_c = data->v_cmd;

  //myown_getenv(data, "OLDPWD", &data->status_of_oldpwd);
  if (!trav_c->cmd[1] || trav_c->cmd[1][0] == '~' || !trav_c->cmd[1][0])
    cd_home_path(data, trav_c->cmd[1]);
  else if (!ft_strcmp(trav_c->cmd[1], "."))
  {
    if (data->old_pwd_make == 0)
      old_pwd_alloc(data);
    get_old_pwd(data, 1);
    //if (check_if_pwd_exist(data))
    //{
    //if (check_if_pwd_exist(data) == 1)
    //  path = alloc_old_pwd(data);
    //else
    //  path = getenv("PWD");
    if (chdir(alloc_old_pwd(data)))
    {
      data->chk_dolla = 1;
      printf("minishell: cd: No such file or directory\n");
      return ;
    }
    data->chk_dolla = 0;
    //}
    return ;
  }
  else if (trav_c->cmd[1][0] == '-')
    cd_between_pwd_and_oldpwd(data, trav_c->cmd[1]);
  else if (!ft_strcmp(trav_c->cmd[1], ".."))
    cd_double_dot(data, trav_c->cmd[1]);
  //else if (trav_c->cmd[1][0] == '/')
  //  cd_to_root(data, trav_c->cmd[1]);
  else if (trav_c->cmd[1][0] != '-' && trav_c->cmd[1][0] != '~' && trav_c->cmd[1][0] != '.' && trav_c->cmd[1])
    cd_path_and_folders(data, trav_c->cmd[1]);
  //another else if it was the path with no / in first and end
  //another one for error
  else
  {
    data->chk_dolla = 1;
    printf("minishell: cd: %s: No such file or directory\n", trav_c->cmd[1]);
  }
}
//here error is env element was not there like ft_strcmp if equal and else if not print and error msg
//also in ./minishell two i should work with the second env that i made
//exit and it's erro $? 1 maybe 
