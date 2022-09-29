/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:34:24 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/29 15:22:09 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  sig_c(int c)
{
  if (c == SIGINT)
  {
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
  }
}

void  new_prompt(void)
{
  rl_on_new_line();
  rl_replace_line("", 0);
}

void  prompt_changer(t_data *data)
{
  t_env *pwd;
  char  *path_h; //this is for ~
  char  *path_pw; //if pwd not exist in env i unset it get dial system
  int   len;
  int   i;
  char  *clr1;
  char  *clr2 = " \e[0m\e[34m \e[0m";

  if (data->chk_dolla == 0)
    clr1 = "\e[40m \e[97m \e[44m\e[30m\e[44m \e[30m";
  else
    clr1 = "\e[103m \e[91m \e[40m\e[93m \e[97m \e[44m\e[30m\e[44m \e[30m";
  pwd = data->l_env;
  //home = data->l_env;
  while (ft_strcmp(pwd->sec, "PWD") && pwd->next)
    pwd = pwd->next;
  if (!ft_strcmp(pwd->sec, "PWD"))
    path_pw = pwd->value;
  else
    path_pw = data->pwd_of_mysys;
  path_h = getenv("HOME");
  if (!path_h)
    path_h = "/Users/hkaddour";
  if (!ft_strncmp(path_pw, path_h, ft_strlen(path_h)))
  {
    if (ft_strlen(path_pw) > ft_strlen(path_h))
    {
      len = ft_strlen(path_h);
      data->prompt = malloc(sizeof(char) * len + 3);
      i = 0;
      data->prompt[i++] = '~';
      while (path_pw[len])
        data->prompt[i++] = path_pw[len++];
      data->prompt[i] = 0;
      data->prompt = ft_strjoin(clr1, ft_strjoin(data->prompt, clr2));
    }
    else if (ft_strlen(path_pw) == ft_strlen(path_h))
    {
      data->prompt = "~";
      data->prompt = ft_strjoin(clr1, ft_strjoin(data->prompt, clr2));
    }
  }
  else
    data->prompt = ft_strjoin(clr1, ft_strjoin(path_pw, clr2));
}

void  make_myown_env(t_data *data)
{
  data->l_env = node_allocate();
  data->l_env->sec = "PWD";
  data->l_env->value = malloc(1024);
  getcwd(data->l_env->value, 1024);
  data->pwd_of_mysys = data->l_env->value;
  data->l_env->next = node_allocate();
  data->l_env->next->sec = "SHLVL";
  data->l_env->next->value = "1";
}

void  add_pwd(t_data *data)
{
  t_env *env;

  env = data->l_env;
  while (env->next)
    env = env->next;
  env->next = node_allocate();
  env = env->next;
  env->sec = "PWD";
  env->value = data->pwd_of_mysys;
}

void  init_shell_elem(t_data *data, char **av, char **env)
{
  data->args = av;
  data->old_pwd_make = 0;
  data->chk_redct_exist = 0;
	data->chk_dolla = 0;
  data->old_pwd_value = ft_strdup("");
  if (!env[0])
    make_myown_env(data);
  else
  {
    data->env = env;
    get_env(data);
    data->pwd_of_mysys = myown_getenv(data, "PWD", &data->status_of_oldpwd);
    if (!data->pwd_of_mysys)
    {
      data->pwd_of_mysys = malloc(sizeof(char) * 1024);
      getcwd(data->pwd_of_mysys, 1024);
      add_pwd(data);
    }
  }
}

void  add_shell_history(t_data *data)
{
  int i;

  i = 0;
  if (data->line[0])
  {
    while (data->line[i] == ' ' || (data->line[i] >= 9 && data->line[i] <= 13))
      i++;
    if (data->line[i])
      add_history(data->line);
  }
}

int main(int ac, char **av, char **envp)
{
  t_data  data;

  if (ac == 1)
  {
    init_shell_elem(&data, av, envp);
    while (1)
    {
      rl_catch_signals = 0;
      signal(SIGINT, sig_c);
      signal(SIGQUIT, SIG_IGN);
      prompt_changer(&data);
      data.line = readline(data.prompt);
      if (!data.line)
      {
      	printf(MOVE_UP_RIGHRT "\t\texit\n");
        exit(131);
      }
      if (data.line[0] == 0)
        new_prompt();
      else
      {
        tokenizer(&data);
        if (!data.error_lexer)
        {
          execution(&data);
        }
      }
      add_shell_history(&data);
      free(data.line);
      //**here should free tokenizer in case of error or normal and parsing nodes
      //this func free all token nodes
      //***here make a condition to free the tokenizer node
	  	//***free_token_node(&data);
    }
    //and here program end should free all shiit
  }
  else
    return (0);
  return (0);
}
