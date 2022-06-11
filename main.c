/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:34:24 by hkaddour          #+#    #+#             */
/*   Updated: 2022/06/11 18:32:17 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  sig_c(int c)
{
  //(void)c;
  //ft_putendl_fd("", 0);
  if (c == SIGINT)
  {
    printf("\n");
    rl_on_new_line();
    //char *cmd[] = {"/bin/stty", 0 };
    //char *cmd_args[] = {" ", "-echoctl", 0};
    //execve(cmd[0], cmd_args, NULL);
    rl_replace_line("", 0);
    rl_redisplay();
    //rl_redisplay();
    //rl_on_new_line();
  }
  else if (c == SIGQUIT)
  {
    printf("\n");
    //rl_on_new_line();
    //rl_redisplay();
    exit(0);
  }
}

t_env *node_allocate(t_data *data)
{
  (void)data;
  t_env *node;

  node = (t_env *) malloc(sizeof(t_env));
  node->sec = NULL;
  node->value = NULL;
  node->next = NULL;
  return (node);
}

void  get_env(t_data *data)
{
  int   i;
  int   j;
  int   k;
  t_env *env;
  t_env *next;
  t_env *trav;

  i = 0;
  env = (t_env *)malloc(sizeof(t_env));
  trav = env;
  while (data->env[i])
  {
    next = node_allocate(data);
    env->next = next;
    env = env->next;
    i++;
  }
  i = 0;
  env = trav;
  while (data->env[i])
  {
    j = 0;
    while (data->env[i][j] && data->env[i][j] != '=')
      j++;
    env->sec = malloc(sizeof(char) * j + 1);
    j = 0;
    while (data->env[i][j] && data->env[i][j] != '=')
    {
      env->sec[j] = data->env[i][j];
      j++;
    }
    env->sec[j] = 0;
    k = ft_strlen(data->env[i]) + 1;
    j++;
    env->value = malloc(sizeof(char) * k - j);
    k = 0;
    while (data->env[i][j] && data->env[i][j] != 0)
    {
      env->value[k] = data->env[i][j];
      j++;
      k++;
    }
    env->value[k] = 0;
    node_allocate(data);
    env = env->next;
    i++;
  }
  env = trav;
  while (trav->next)
  {
    printf("%s=%s\n", trav->sec, trav->value);
    trav = trav->next;
  }
}

void  get_path(t_data *data)
{
  int   i;
  int   j;
  int   k;

  i = 0;
  j = 5;
  while (data->env[i] && ft_strncmp(data->env[i], "PATH=", 5))
    i++;
  while (data->env[i][j] && data->env[i][j])
    j++;
  data->w_path = malloc(sizeof(char) * j + 1);
  //ft_strdup(data->env[i]);
  j = 5;
  k = 0;
  while (data->env[i][j])
  {
    data->w_path[k] = data->env[i][j];
    j++;
    k++;
  }
  data->w_path[k] = 0;
}

void  excute(t_data *data)
{
  int i;

  i = 0;
  get_path(data);
  data->cmd = ft_split(data->line, ' ');
  data->split = ft_split(data->w_path, ':');
  while (data->split[i])
  {
    data->abs_path = ft_strjoin(ft_strjoin(data->split[i], "/"), data->cmd[0]);
    //printf("%s\n", data->abs_path);
    if (!access(data->abs_path, F_OK))
    {
      execve(data->abs_path, data->cmd, data->env);
    }
    free(data->abs_path);
    i++;
  }
}

void  execute_cmd(t_data *data)
{
  int pid;

  pid = fork();
  if (pid < 0)
    exit(2);
  else if (pid == 0)
  {
    excute(data);
  }
  else
  {
    wait(0);
    return ;
  }
}

int main(int ac, char **av, char **envp)
{
  t_data  data;
  int     i;
  char    prompt[] = "$Minishell> ";

  i = 0;
  (void)ac;
  data.args = av;
  data.env = envp;
  //write(0, &prompt, sizeof(prompt));
  while (1)
  {
    //line = grab_line(0);
    signal(SIGINT, sig_c);
    signal(SIGQUIT, sig_c);
    //printf("%d\n", getpid());
    data.line = readline(prompt);
    if (!data.line)
      return (0);
    if (!ft_strncmp(data.line, "exit", 4))
    {
      free(data.line);
      exit(0);
    }
    if (!ft_strncmp(data.line, "cd", 4))
      chdir("/Users/hkaddour/");
    //get_env(&data);
    execute_cmd(&data);
    //excute(&data);
    //get_path(&data);
    //printf("%s\n", data.w_path);
    //excute(&data);
    //get_path(&data);
    //printf("%s\n", data.w_path);
    //data.split = ft_split(data.w_path, ':');
    //while (data.split[i])
    //{
    //  printf("%s\n", data.split[i]);
    //  i++;
    //}
    //printf("%s\n", data.line);
    //get_path(&data);
    //printf("%s\n", data.w_path);
    //while (data.w_path[i])
    //  printf("%d\n", data.w_path[i++]);
    add_history(data.line);
    free(data.line);
    //write(0, &prompt, sizeof(prompt));
  }
  return (0);
}
//pseudo code:
//recursive descent paser algo:
//first read line
//make a scanner that generate tokens for each cmd and error
//handle the Ctrl-C ... just int he minishel prompt.
