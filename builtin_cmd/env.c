/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:11:41 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/20 14:04:35 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *node_allocate(void)
{
  t_env *node;

  node = (t_env *) malloc(sizeof(t_env));
  node->sec = 0;
  node->value = 0;
  node->next = 0;
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

  i = 1;
  //env = (t_env *)malloc(sizeof(t_env));
  //env->sec = 0;
  //env->value = 0;
  //env->next = 0;
  //data->l_env = env;
  env = node_allocate();
  trav = env;
  while (data->env[i])
  {
    if (!ft_strncmp(data->env[i], "OLDPWD", ft_strlen("OLDPWD")))
      i++;
    next = node_allocate();
    env->next = next;
    env = env->next;
    i++;
  }
  i = 0;
  env = trav;
  while (data->env[i])
  {
    j = 0;
    if (!ft_strncmp(data->env[i], "OLDPWD", ft_strlen("OLDPWD")))
      i++;
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
    //here pass the equal sign
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
    //why did u add another node allocate this one just added leaks and i didn't use it
    //node_allocate(data);
    env = env->next;
    i++;
  }
  env = trav;
  data->l_env = env;
  //add one to the indent level
  while (ft_strncmp(trav->sec, "SHLVL", 5))
    trav = trav->next;
  //i = ft_strlen(trav->value) - 1;
  //trav->value[i] += 1;
  int shlvl;
  data->shlvl_ptr = trav;
  shlvl = ft_atoi(trav->value);
  shlvl++;
  free(trav->value);
  data->shlvl_ptr->value = ft_itoa(shlvl);
  //trav->value = ft_itoa(shlvl);

  //while (trav->next)
  //{
  //  printf("%s=%s\n", trav->sec, trav->value);
  //  trav = trav->next;
  //}
}

void  env_cmd(t_data *data)
{
  t_env *trav;

  trav = data->l_env;
  while (trav)
  {
    printf("%s=%s\n", trav->sec, trav->value);
    trav = trav->next;
  }
}
