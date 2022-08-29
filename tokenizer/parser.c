/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:32:56 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/29 17:18:40 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  len_cmd(t_token *trav)
{
  int i;
  int j;

  i = 0;
  while (trav)
  {
    if (trav->type == PIPE)
      break ;
    j = 0;
    while (trav->value[j])
    {
      j++;
      i++;
    }
    trav = trav->next;
  }
  return (i);
}

static void  split_cmd(t_data *data)
{
  int     i;
  int     j;
  int     k;
  //int     check;
  t_token *trav;
  t_token *hold;

  i = 0;
  j = 0;
  //check = 1;
  trav = data->t_token;
  hold = data->t_token;
  while (trav)
  {
    if (trav->type == PIPE && &trav->type != &hold->type)
      i++;
    trav = trav->next;
  }
  data->split_cmd = malloc(sizeof(char *) * i + 2);
  trav = data->t_token;
  while (trav)
  {
    i = 0;
    data->split_cmd[j] = malloc(sizeof(char) * len_cmd(trav));
    while (trav->type != PIPE)
    {
      k = 0;
      while (trav->value[k])
        data->split_cmd[j][i++] = trav->value[k++];
      trav = trav->next;
      if (!trav)
        break ;
    }
    if (trav)
    {
      if (trav->type == PIPE && &trav->type == &hold->type)
      {
        //check--;
        trav = trav->next;
        continue ;
      }
    }
    data->split_cmd[j][i] = 0;
    j++;
    if (!trav)
      break ;
    trav = trav->next;
  }
  data->split_cmd[j] = NULL;
}

static char *str_put(char *arg, int len)
{
  int   i;
  char  *ptr;

  i = 0;
  ptr = malloc(sizeof(char) * len + 1);
  while (&arg[i] != &arg[len])
  {
    ptr[i] = arg[i];
    i++;
  }
  ptr[i] = 0;
  return (ptr);
}

static void  allocate_parsing(t_data *data)
{
  int     i;
  int     j;
  int     cmd_len;
  int     file_len;
  //char    *arg;
  t_types typ;

  i = 0;
  j = 0;
  cmd_len = 0;
  file_len = 0;
  while (data->split_cmd[i])
  {
    while (data->split_cmd[i][j])
    {
      if (data->split_cmd[i][j] != '>')
      {
        //arg = str_put(data->split_cmd[i], j);
        j++;
        if (data->split_cmd[i][j] == '>')
        {
          typ = O_APEND;
          j += 2;
          while (data->split_cmd[i][j] != ' ')
          {
            file_len++;
            j++;
          }
          //if (data->split_cmd[i][j] == ' ')
        }
        else if (data->split_cmd[i][j] != '>')
        {
          typ = O_TRNC;

        }
      }
      if (data->split_cmd[i][j] == '<')
      {
        j++;
        if (data->split_cmd[i][j] == '<')
        {

        }
      }
      cmd_len++;
      j++;
    }
    i++;
  }
}

void  parser(t_data *data)
{
  split_cmd(data);
  allocate_parsing(data);
  //this fucntion i should allocate the cmd with the file and in and out file
  int i;

  i = 0;
  while (data->split_cmd[i])
  {
    printf("%s\n", data->split_cmd[i]);
    i++;
  }
}
