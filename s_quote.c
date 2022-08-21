/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:46:15 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/21 19:32:08 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  token_s_quote(t_data *data)
{
  int   i;
  int   j;
  int   len;
  char  *ptr;
  char  *dolla;
  t_env *trav;

  i = 0;
  j = 0;
  trav = data->l_env;
  ptr = malloc(sizeof(char) * 100);
  while (data->line[i])
  {
    if (data->line[i] == '\'')
    {
      i++;
      while (data->line[i] != '\'' && data->line[i])
      {
        ptr[j] = data->line[i];
        i++;
        j++;
      }
      if (data->line[i] == '\'')
        i++;
    }
    else if (data->line[i] == '\"')
    {
      i++;
      //while (data->line[i] != '$' && data->line[i] != '\'' && data->line[i] != '\"' && data->line[i])
      while (data->line[i] != '$' && data->line[i] != '\"' && data->line[i])
      {
        ptr[j] = data->line[i];
        i++;
        j++;
      }
      while (data->line[i] == '$')
      {
        i++;
        len = 0;
        while (ft_acceptable_char(data->line[i]))
        {
          i++;
          len++;
        }
        dolla = malloc(sizeof(char) * len + 1);
        i -= len;
        len = 0;
        while (ft_acceptable_char(data->line[i]))
        {
          dolla[len] = data->line[i];
          i++;
          len++;
        }
        dolla[len] = 0;
        while (ft_strncmp(trav->sec, dolla, len) && trav->next != NULL)
          trav = trav->next;
        if (!ft_strncmp(trav->sec, dolla, len))
        {
          free(dolla);
          dolla = ft_strdup(trav->value);
        }
        else
        {
          free(dolla);
          dolla = ft_strdup("");
        }
        len = 0;
        while (dolla[len])
        {
          ptr[j] = dolla[len];
          j++;
          len++;
        }
        trav = data->l_env;
      }
      if (data->line[i] == '\"' || data->line[i] == '\'')
      {
        if (data->line[i] == '\'')
        {
          ptr[j] = data->line[i];
          i++;
          j++;
        }
        else if (data->line[i] == '\"')
          i++;
      }
    }
    while (data->line[i] == '$')
    {
      i++;
      len = 0;
      while (ft_acceptable_char(data->line[i]))
      {
        i++;
        len++;
      }
      dolla = malloc(sizeof(char) * len + 1);
      i -= len;
      len = 0;
      while (ft_acceptable_char(data->line[i]))
      {
        dolla[len] = data->line[i];
        i++;
        len++;
      }
      dolla[len] = 0;
      while (ft_strncmp(trav->sec, dolla, len) && trav->next != NULL)
        trav = trav->next;
      if (!ft_strncmp(trav->sec, dolla, len))
      {
        free(dolla);
        dolla = ft_strdup(trav->value);
      }
      else
      {
        free(dolla);
        dolla = ft_strdup("");
      }
      len = 0;
      while (dolla[len])
      {
        ptr[j] = dolla[len];
        j++;
        len++;
      }
      trav = data->l_env;
    }
    //else
    //{
      while (data->line[i] != '\'' && data->line[i] != '\"' && data->line[i])
      {
        ptr[j] = data->line[i];
        i++;
        j++;
      }
    //}
    //i++;
  }
  ptr[j] = 0;
  printf("%s\n", ptr);
}
//'$cool'





//if (data->line[i] == '$')
//{
//  i++;
//  k = 0;
//  while (ft_acceptable_char(data->line[i]))
//  {
//    i++;
//    k++;
//    //dolla[k] = data->line[i];
//  }
//  dolla = malloc(sizeof(char) * k + 1);
//  i = i - k;
//  k = 0;
//  while (ft_acceptable_char(data->line[i]))
//  {
//    dolla[k] = data->line[i];
//    k++;
//    i++;
//  }
//}
