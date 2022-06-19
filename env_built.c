/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:52:21 by hkaddour          #+#    #+#             */
/*   Updated: 2022/06/19 19:05:15 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  reinit_env(t_data *data)
{
  t_env *trav;

  get_env(data);
  trav = data->l_env;
  while (ft_strncmp(trav->sec, "PWD", 3))
    trav = trav->next;
  free(trav->value);
  //trav->value = malloc(sizeof(char) * ft_strlen(data->cd_path) + 1);
  trav->value = data->cd_path;
}

void  pwd_cmd(t_data *data)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strncmp(trav->sec, "PWD", 3))
    trav = trav->next;
  if (data->built_cmd->type == WRD)
  {
    printf("%s\n", trav->value);
  }
}

void  env_cmd(t_data *data)
{
  //maybe all white space check
  t_env *trav;

  trav = data->l_env;
  //if (data->built_cmd->next->type == W_SPACE || data->built_cmd->next == NULL)
  if (data->built_cmd->next != NULL)
  {
    if (data->built_cmd->next->type != W_SPACE)
    {
      error("minishel: env env no\n", 1);
      return ;
    }
  }//I have to check error in all the line
  if (/*data->built_cmd->next->type == W_SPACE ||*/ data->built_cmd != NULL)
  {
    while (trav->next)
    {
      printf("%s=%s\n", trav->sec, trav->value);
      trav = trav->next;
    }
  }
  //else
  //  error("minishel: env env no\n", 1);
}

//handle a lot of echos and "" and $ on it
void  echo_cmd(t_data *data)
{
  t_token *trav;

  if (data->built_cmd->next == NULL)
    printf("empty line\n");//take that msg off later
  if (data->built_cmd->next->type != W_SPACE)
  {
    error("minishell: you need to sprate with space", 1);
    return ;
  }
  if (data->built_cmd->next->type == W_SPACE)
  {
    trav = data->built_cmd->next;
    if (trav->next->type == WRD)
    {
      trav = trav->next;
      while (trav)
      {
        //here check if the next value have $ or "" and more
        //
        printf("%s", trav->value);
        trav = trav->next;
      }
      printf("\n");
    }
  }
}










