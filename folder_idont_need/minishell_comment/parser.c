/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:42:42 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/23 10:48:29 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void  add_node(t_data *data, t_types typ)
//{
//  t_token *node;
//  //char  *w_end;
//  int i;
//
//  //i = 0;
//  //while (str[i] != ' ')
//  //  i++;
//  //w_end = &str[i];
//  node = (t_token *) malloc(sizeof(t_token));
//  node->type = typ;
//  node->value = malloc(sizeof(char) * data->i_line + 1);
//  //w_end = check_word(str);
//  i = 0;
//  while (str != w_end)
//  {
//    node->value[i] = str[i];
//    i++;
//  }
//  node->value[i] = 0;
//  node->next = NULL;
//}

void  node_head(t_data *data)
{
  data->t_token = (t_token *) malloc(sizeof(t_token));
  data->t_token->type = 0;
  data->t_token->value = NULL;
  data->t_token->next = NULL;
}

int ft_acceptable_char(int c)
{
  if (c >= 48 && c <= 57)
    return (1);
  else if (c >= 65 && c <= 90)
    return (1);
  else if (c >= 97 && c <= 122)
    return (1);
  //maybe i gotta add '-' she is printable
  else
    return (0);
}

//void  add_node(t_data *data, t_types typ, int check)
void  add_node(t_data *data, t_types typ)
{
  int     i;
  int     j;
  int     keep;
  int     s_quote;
  int     d_quote;
  t_token *node;
  t_token *trav;
  t_env   *trav_env;

  trav_env = data->l_env;
  s_quote = 0;
  d_quote = 0;
  node = (t_token *) malloc(sizeof(t_token));
  if (data->check == 1)
  {
    data->t_token = node;
    //data->check--;
    //data->check = 0;
  }
  //if (check == 1)
  //  data->t_token = node;
  node->type = typ;
  //this if just for D_QUOT make the S_QUOT
  //if (typ == D_QUOT || typ == S_QUOT)

  //if (typ == D_QUOT)
  //{
  //  i = 0;
  //  j = 0;
  //  //here i should go and count inside of the env $ and make some ptr to point 
  //  //still the problem in the &data->n_line[0] && data->n_line[i]
  //  //**while (&data->beg_line[i] != &data->n_line[0])
  //  //**{
  //  //**  if (data->beg_line[i] == '\"')
  //  //**    j++;
  //  //**  i++;
  //  //**}
  //  //node->value = malloc(sizeof(char) * (data->i_line - j) + 1);
  //  node->value = malloc(sizeof(char) * 100 + 1);
  //  i = 0;
  //  j = 0;
  //  //while (&data->beg_line[i] != &data->n_line[0] || &data->beg_line[i])
  //  //while (&data->beg_line[j] != &data->n_line[0] && data->beg_line[i])
  //  while (&data->beg_line[i + 1] != &data->n_line[0] && data->beg_line[i])
  //  {
  //    //if (&data->beg_line[i] == '\"' || &data->beg_line[i] == '\'')
  //    //if (&data->beg_line[i] == &data->n_line[0])
  //    //  break ;
  //    //while (data->beg_line[i] == '\"' || data->beg_line[i] == '\'')
  //    while (data->beg_line[i] == '\"' || data->beg_line[i] == '\'')
  //    {
  //      if (data->beg_line[i] == '\"')
  //      {
  //        i++;
  //        d_quote++;
  //      }
  //      else if (data->beg_line[i] == '\'')
  //      {
  //        if (d_quote % 2 == 0)
  //        {
  //          i++;
  //          s_quote++;
  //        }
  //        else
  //        {
  //          s_quote++;
  //          node->value[j] = data->beg_line[i];
  //          i++;
  //          j++;
  //          //break ;
  //        }
  //      }
  //    }

  //    //while (data->beg_line[i] == '\"')
  //    //{
  //    //  if (data->beg_line[i] == '\"' && s_quote % 2 == 0)
  //    //  {
  //    //    i++;
  //    //    d_quote++;
  //    //  }
  //    //  else
  //    //    s_quote++;
  //    //}

  //    //here also should not work in ''
  //    //if (data->beg_line[i] == '$')
  //    //gad blan if single quote '' don't print the actual env $variable
  //    //while (data->beg_line[i] == '$' && d_quote % 2 == 1)
  //    //if (data->beg_line[i] == '$' && d_quote % 2 == 1 && (s_quote % 2 == 1 || s_quote % 2 == 0))
  //    //this for "'$'"$
  //    //if (data->beg_line[i] == '$' || (d_quote % 2 == 1 && (s_quote % 2 == 1 || s_quote % 2 == 0)) \
  //    //    || (d_quote % 2 == 0 && s_quote % 2 == 0))
  //    //{

  //    //}
  //    //this for ""'$'
  //    //else if (data->beg_line[i] == '$' && d_quote % 2 == 0 && s_quote % 2 == 1)
  //    //{

  //    //}
  //    //if (data->beg_line[i] == '$')
  //    //{
  //      //if ((d_quote % 2 == 1 && (s_quote % 2 == 1 || s_quote % 2 == 0)) || (d_quote % 2 == 0 && s_quote % 2 == 0))
  //      //if ((d_quote % 2 == 1 && s_quote % 2 == 1) || (d_quote % 2 == 1 && s_quote % 2 == 0) ||\
  //      //    (d_quote % 2 == 0 && s_quote % 2 == 0))
  //      //if (!(d_quote % 2 == 0 && s_quote % 2 == 1))
  //      //{//here
  //    while (data->beg_line[i] == '$')
  //    {
  //      if (data->beg_line[i + 1] == ' ' || data->beg_line[i + 1] == '\"' \
  //          || data->beg_line[i + 1] == '\'' /*|| data->beg_line[i + 1] == '\0'*/)
  //      {
  //        node->value[j] = data->beg_line[i];
  //        i++;
  //        j++;
  //        break ;
  //      }
  //      else if (data->beg_line[i + 1] == 0)
  //      {
  //        node->value[j] = data->beg_line[i];
  //        i++;
  //        j++;
  //        break ;
  //      }
  //      else if (data->beg_line[i + 1] == '?')
  //      {
  //        //maybe here i should put the number on how the process got ended
  //        keep = i + 1;
  //        while (i <= keep)
  //        {
  //          node->value[j] = data->beg_line[i];
  //          i++;
  //          j++;
  //        }
  //        break ;
  //      }
  //      else if (data->beg_line[i + 1] == '$')
  //      {
  //        i += 2;
  //        break ;
  //      }
  //      //added now
  //      //if (!(d_quote % 2 == 0 && s_quote % 2 == 1))
  //      i++;
  //      char  *dolla;
  //      int   len;

  //      len = 0;
  //      while (ft_acceptable_char(data->beg_line[i]))
  //      {
  //        i++;
  //        len++;
  //      }
  //      //here i will count $ i put it in the array of node->value
  //      if (!(d_quote % 2 == 0 && s_quote % 2 == 1))
  //        dolla = malloc(sizeof(char) * len + 2);
  //      else
  //        dolla = malloc(sizeof(char) * len + 1);
  //      i = i - len;
  //      len = 0;
  //      if (d_quote % 2 == 0 && s_quote % 2 == 1)
  //      {
  //        dolla[len] = '$';
  //        len++;
  //      }
  //      while (ft_acceptable_char(data->beg_line[i]))
  //      {
  //        dolla[len] = data->beg_line[i];
  //        i++;
  //        len++;
  //      }
  //      dolla[i] = 0;
  //      //while (ft_strncmp(trav_env->sec, dolla, i) && trav_env->next != NULL)
  //      //  trav_env = trav_env->next;
  //      if (!(d_quote % 2 == 0 && s_quote % 2 == 1))
  //      {
  //        while (ft_strncmp(trav_env->sec, dolla, i) && trav_env->next != NULL)
  //          trav_env = trav_env->next;
  //        if (!ft_strncmp(trav_env->sec, dolla, i))
  //        {
  //          free(dolla);
  //          dolla = ft_strdup(trav_env->value);
  //        }
  //        else
  //        {
  //          free(dolla);
  //          dolla = ft_strdup("");
  //          //dolla = ft_strdup(" ");
  //          //maybe here is the problem
  //        }
  //      }
  //      //**if (!ft_strncmp(trav_env->sec, dolla, i))
  //      //**{
  //      //**  free(dolla);
  //      //**  dolla = ft_strdup(trav_env->value);
  //      //**}
  //      //**else
  //      //**{
  //      //**  free(dolla);
  //      //**  //dolla = ft_strdup("");
  //      //**  dolla = ft_strdup(" ");
  //      //**  //maybe here is the problem
  //      //**}
  //      trav_env = data->l_env;
  //      len = 0;
  //      while (dolla[len])
  //      {
  //        node->value[j] = dolla[len];
  //        j++;
  //        len++;
  //      }
  //      dolla = NULL;
  //      while (data->beg_line[i] == '\"' || data->beg_line[i] == '\'')
  //      {
  //        if (data->beg_line[i] == '\"')
  //        {
  //          i++;
  //          d_quote++;
  //        }
  //        else if (data->beg_line[i] == '\'')
  //        {
  //          if (d_quote % 2 == 0)
  //          {
  //            i++;
  //            s_quote++;
  //          }
  //          else
  //          {
  //            s_quote++;
  //            node->value[j] = data->beg_line[i];
  //            i++;
  //            j++;
  //            //break ;
  //          }
  //        }
  //      }
  //    }
  //      //else if (data->beg_line[i] == '$' && d_quote % 2 == 0 && s_quote % 2 == 1)
  //      //else
  //      //{
  //      //  printf("lalal");
  //      //}
  //    //}
  //    //**while (data->beg_line[i] == '$' && (d_quote % 2 == 0 || s_quote % 2 == 0))
  //    //**{
  //    //**  //i++;
  //    //**  //if (data->beg_line[i + 1] == ' ' || data->beg_line[i + 1] == '\"' || data->beg_line[i + 1] == '\'' || data->beg_line[i])
  //    //**  if (data->beg_line[i + 1] == ' ' || data->beg_line[i + 1] == '\"' \
  //    //**      || data->beg_line[i + 1] == '\'' /*|| data->beg_line[i + 1] == '\0'*/)
  //    //**  {//maybe i need to take off '' in the if statement
  //    //**    node->value[j] = data->beg_line[i];
  //    //**    i++;
  //    //**    j++;
  //    //**    break ;
  //    //**  }
  //    //**  else if (data->beg_line[i + 1] == 0)
  //    //**  {
  //    //**    node->value[j] = data->beg_line[i];
  //    //**    i++;
  //    //**    j++;
  //    //**    break ;
  //    //**  }
  //    //**  else if (data->beg_line[i + 1] == '?')
  //    //**  {
  //    //**    keep = i + 1;
  //    //**    while (i <= keep)
  //    //**    {
  //    //**      node->value[j] = data->beg_line[i];
  //    //**      i++;
  //    //**      j++;
  //    //**    }
  //    //**    break ;
  //    //**  }
  //    //**  else if (data->beg_line[i + 1] == '$')
  //    //**  {
  //    //**    //i++;
  //    //**    //while (data->beg_line[i])
  //    //**    //
  //    //**    //node->value[j] = ' ';
  //    //**    //
  //    //**    //node->value[j] = 0;
  //    //**    //
  //    //**    //j++;
  //    //**    //
  //    //**    //i++;
  //    //**    //while (data->beg_line[i] == '$')
  //    //**    //{

  //    //**    //}
  //    //**    i += 2;
  //    //**    //i++;
  //    //**    break ;
  //    //**  }
  //    //**  //**else if (data->beg_line[i + 1] == '>' || data->beg_line[i + 1] == '|' || data->beg_line[i + 1] == '<')
  //    //**  //**{

  //    //**  //**}
  //    //**  //here check if the next index is $ so to put " " a space same with the up one
  //    //**  i++;
  //    //**  char  *dolla;
  //    //**  int   len;

  //    //**  len = 0;
  //    //**  //while (data->beg_line[i] != ' ' && data->beg_line[i] != '\"' && data->beg_line[i] != '|' && data->beg_line[i] != '>' \
  //    //**  //    && data->beg_line[i] != '<' && data->beg_line[i] != '$' && data->beg_line[i] /*and maybe single quote also*/)
  //    //**  while (ft_acceptable_char(data->beg_line[i]))
  //    //**  {
  //    //**    i++;
  //    //**    len++;
  //    //**  }
  //    //**  dolla = malloc(sizeof(char) * len + 1);
  //    //**  i = i - len;
  //    //**  len = 0;
  //    //**  //while (data->beg_line[i] != ' ' && data->beg_line[i] != '\"' && data->beg_line[i] != '|' && data->beg_line[i] != '>' \
  //    //**  //    && data->beg_line[i] != '<' && data->beg_line[i] != '$' && data->beg_line[i] /*and maybe single quote also*/)
  //    //**  while (ft_acceptable_char(data->beg_line[i]))
  //    //**  {
  //    //**    dolla[len] = data->beg_line[i];
  //    //**    i++;
  //    //**    len++;
  //    //**  }
  //    //**  dolla[i] = 0;
  //    //**  while (ft_strncmp(trav_env->sec, dolla, i) && trav_env->next != NULL)
  //    //**    trav_env = trav_env->next;
  //    //**  //here trav_env always initialize it with the head of env
  //    //**  //if empty
  //    //**  if (!ft_strncmp(trav_env->sec, dolla, i))
  //    //**  {
  //    //**    free(dolla);
  //    //**    dolla = ft_strdup(trav_env->value);
  //    //**  }
  //    //**  else
  //    //**  {
  //    //**    free(dolla);
  //    //**    //dolla = ft_strdup(" ");
  //    //**    dolla = ft_strdup("");
  //    //**    //here i need only newline not space
  //    //**  }
  //    //**  trav_env = data->l_env;
  //    //**  len = 0;
  //    //**  while (dolla[len])
  //    //**  {
  //    //**    node->value[j] = dolla[len];
  //    //**    j++;
  //    //**    len++;
  //    //**  }
  //    //**  while (data->beg_line[i] == '\"' || data->beg_line[i] == '\'')
  //    //**  {
  //    //**    if (data->beg_line[i] == '\"')
  //    //**    {
  //    //**      i++;
  //    //**      d_quote++;
  //    //**    }
  //    //**    else if (data->beg_line[i] == '\'')
  //    //**    {
  //    //**      if (d_quote % 2 == 0)
  //    //**        i++;
  //    //**      else
  //    //**        break ;
  //    //**    }
  //    //**  }
  //    //**  //send it to a function that malloc that shiit and then 

  //    //**}

  //    //maybe i'am not longer needing this
  //    //while (data->beg_line[i] == '\"')
  //    while (data->beg_line[i] == '\"' || data->beg_line[i] == '\'')
  //    {
  //      if (data->beg_line[i] == '\"')
  //      {
  //        i++;
  //        d_quote++;
  //      }
  //      //else if (data->beg_line[i] == '\'' && d_quote % 2 == 0)
  //      else if (data->beg_line[i] == '\'')
  //      {
  //        if (d_quote % 2 == 0)
  //        {
  //          i++;
  //          s_quote++;
  //        }
  //        else
  //        {
  //          s_quote++;
  //          node->value[j] = data->beg_line[i];
  //          i++;
  //          j++;
  //          //break ;
  //        }
  //      }
  //    }

  //    //if (data->beg_line[i] == '\"' || data->beg_line[i] == '\'')
  //    //{
  //    //  //if (&data->beg_line[j] != &data->n_line[0])
  //    //  i++;
  //    //  if (data->beg_line[i] == '\"' || data->beg_line[i] == '\'')
  //    //    i++;
  //    //}
  //    if (&data->beg_line[i + 1] == &data->n_line[0])
  //      break ;
  //    //**just add it i will put it in a function
  //    //**if (data->beg_line[i] == '$')
  //    //**{
  //    //**  i++;
  //    //**  char  *dolla;
  //    //**  int   len;

  //    //**  len = 0;
  //    //**  while (data->beg_line[i] != ' ' && data->beg_line[i] != '\"' && data->beg_line[i] != '|' \
  //    //**      && data->beg_line[i] != '>' && data->beg_line[i] != '<' && data->beg_line[i] != '$' && data->beg_line[i] /*and maybe single quote also*/)
  //    //**  {
  //    //**    i++;
  //    //**    len++;
  //    //**  }
  //    //**  dolla = malloc(sizeof(char) * len + 1);
  //    //**  i = i - len;
  //    //**  len = 0;
  //    //**  while (data->beg_line[i] != ' ' && data->beg_line[i] != '\"' && data->beg_line[i] != '|' \
  //    //**      && data->beg_line[i] != '>' && data->beg_line[i] != '<' && data->beg_line[i] != '$' && data->beg_line[i] /*and maybe single quote also*/)
  //    //**  {
  //    //**    dolla[len] = data->beg_line[i];
  //    //**    i++;
  //    //**    len++;
  //    //**  }
  //    //**  dolla[i] = 0;
  //    //**  while (ft_strncmp(trav_env->sec, dolla, i) && trav_env->next != NULL)
  //    //**    trav_env = trav_env->next;
  //    //**  //here trav_env always initialize it with the head of env
  //    //**  //if empty
  //    //**  if (!ft_strncmp(trav_env->sec, dolla, i))
  //    //**  {
  //    //**    free(dolla);
  //    //**    dolla = ft_strdup(trav_env->value);
  //    //**  }
  //    //**  else
  //    //**  {
  //    //**    free(dolla);
  //    //**    dolla = ft_strdup(" ");
  //    //**  }
  //    //**  len = 0;
  //    //**  while (dolla[len])
  //    //**  {
  //    //**    node->value[j] = dolla[len];
  //    //**    j++;
  //    //**    len++;
  //    //**  }
  //    //**  trav_env = data->l_env;
  //    //**  //send it to a function that malloc that shiit and then 
  //    //**}
  //    //** end
  //    //if (data->beg_line[i] == '$')
  //    //{

  //    //}
  //    //just try this one for $$$
  //    if (data->beg_line[i] != '$')
  //    {
  //      node->value[j] = data->beg_line[i];
  //      i++;
  //      //if (data->beg_line[j] != '\"' || data->beg_line[j] != '\'')
  //      j++;
  //    }
  //  }
  //  //data->beg_line = &data->beg_line[j];
  //  data->beg_line = &data->beg_line[i];
  //  //check this one maybe i did miss the index 
  //  node->value[j] = 0;
  //}
  //
 //***************
  //else if (typ == S_QUOT)
  //{
  //  int quote_pos;
  //  int s_pos;
  //  int d_pos;
  //  i = 0;
  //  j = 0;
  //  s_pos = 0;
  //  d_pos = 0;
  //  quote_pos = 0;
  //  node->value = malloc(sizeof(char) * 100 + 1);
  //  //while (&data->beg_line[j] != &data->n_line[0] && data->beg_line[i])
  //  while (&data->beg_line[i + 1] != &data->n_line[0] && data->beg_line[i])
  //  {
  //    while (data->beg_line[i] == '\'' || data->beg_line[i] == '\"')
  //    {
  //      if (data->beg_line[i] == '\'')
  //      {
  //        quote_pos = 2;
  //        s_pos = 2;
  //        s_quote++;
  //        //if (d_quote % 2 == 0 && s_quote % 2 == 1)
  //        if (d_quote % 2 == 0)
  //        {
  //          i++;
  //          //s_quote++;
  //        }
  //        //else if (d_quote % 2 == 1 && s_quote % 2 == 1)
  //        //else if (d_quote % 2 == 1 && s_quote % 2 == 1)
  //        //{
  //        //  i++;
  //        //  //s_quote++;
  //        //}
  //        //else if (d_quote % 2 == 1 && s_quote % 2 == 0)
  //        else if (d_quote % 2 == 1 /*&& s_quote % 2 == 0*/)
  //        {
  //          if (s_quote % 2 == 0)
  //            i++;
  //          else if (s_quote % 2 == 1)
  //          {
  //            //s_quote++;
  //            node->value[j] = data->beg_line[i];
  //            i++;
  //            j++;
  //          }
  //        }
  //        //i++; 
  //        //s_quote++;
  //      }
  //      else if (data->beg_line[i] == '\"')
  //      {
  //        quote_pos = 4;
  //        d_pos = 4;
  //        if (s_quote % 2 == 0)
  //        {
  //          i++;
  //          d_quote++;
  //        }
  //        else
  //        {
  //          d_quote++;
  //          node->value[j] = data->beg_line[i];
  //          i++;
  //          j++;
  //        }
  //      }
  //    }
  //    //***
  //    while (data->beg_line[i] == '$')
  //    {
  //      if (data->beg_line[i + 1] == ' ' || data->beg_line[i + 1] == '\"' \
  //          || data->beg_line[i + 1] == '\'')
  //      {
  //        node->value[j] = data->beg_line[i];
  //        i++;
  //        j++;
  //        break ;
  //      }
  //      else if (data->beg_line[i + 1] == 0)
  //      {
  //        node->value[j] = data->beg_line[i];
  //        i++;
  //        j++;
  //        break ;
  //      }
  //      //else if (data->beg_line[i + 1] == '?' && s_quote % 2 == 0)
  //      else if (data->beg_line[i + 1] == '?')
  //      {
  //        //maybe here i should put the number on how the process got ended
  //        //cuz if '$?' should be print but in ''$? should print end of process
  //        keep = i + 1;
  //        while (i <= keep)
  //        {
  //          node->value[j] = data->beg_line[i];
  //          i++;
  //          j++;
  //        }
  //        break ;
  //      }
  //      //else if (data->beg_line[i + 1] == '$' && s_quote % 2 == 1)
  //      else if (data->beg_line[i + 1] == '$')
  //      {
  //        //if only '' was open then i will print all $$ if close with "" or without try to print the value
  //        if (s_quote % 2 == 1 || (d_pos == 4 && s_pos == 2 && quote_pos == 2 && s_quote < 2))
  //        {
  //          while (data->beg_line[i] == '$' && data->beg_line[i] != '\'' && data->beg_line[i] != '\"')
  //          {
  //            node->value[j] = data->beg_line[i];
  //            i++;
  //            j++;
  //          }
  //          break ;
  //        }
  //        //else if (s_quote % 2 == 1 || (d_pos == 4 && s_pos == 2 && quote_pos == 2))
  //        else
  //        {
  //          i += 2;
  //          break ;
  //        }
  //        //i += 2;
  //        //break ;
  //      }
  //      ///****
  //      // this one will copy in the below one
  //      //if (s_quote % 2 == 1)
  //      //{
  //      //  while ()
  //      //}
  //      //if (s_quote % 2 == 0 || quote_pos == 2)
  //      if (s_quote % 2 == 0 || (d_pos == 4 && s_pos == 2 && quote_pos == 2))
  //      {//and here if '' are closed and "" open so to add "" or take it off
  //        i++;
  //        char  *dolla;
  //        int   len;

  //        len = 0;
  //        //here if it reach the end \0
  //        while (ft_acceptable_char(data->beg_line[i]))
  //        {
  //          i++;
  //          len++;
  //        }
  //        dolla = malloc(sizeof(char) * len + 1);
  //        i = i - len;
  //        len = 0;
  //        while (ft_acceptable_char(data->beg_line[i]))
  //        {
  //          dolla[len] = data->beg_line[i];
  //          i++;
  //          len++;
  //        }
  //        dolla[i] = 0;
  //        //if (!(d_quote % 2 == 0 && s_quote % 2 == 1))
  //        //{
  //          while (ft_strncmp(trav_env->sec, dolla, i) && trav_env->next != NULL)
  //            trav_env = trav_env->next;
  //          if (!ft_strncmp(trav_env->sec, dolla, i))
  //          {
  //            free(dolla);
  //            dolla = ft_strdup(trav_env->value);
  //          }
  //          else
  //          {
  //            free(dolla);
  //            //dolla = ft_strdup(" ");
  //            dolla = ft_strdup("");
  //          }
  //        //}
  //        trav_env = data->l_env;
  //        len = 0;
  //        while (dolla[len])
  //        {
  //          node->value[j] = dolla[len];
  //          j++;
  //          len++;
  //        }
  //        dolla = NULL;
  //        //if (d_quote % 2 == 1)
  //        //{

  //        //}
  //        //else if (d_quote % 2 == 0)
  //        //{
  //        //  //here if equal to '' or "" just count it and move on
  //        //}
  //      }
  //      else
  //      {
  //        node->value[j] = data->beg_line[i];
  //        i++;
  //        j++;
  //        //i++;
  //        //while (data->beg_line[i] != '\'' && data->beg_line[i] != '\"' && data->beg_line[i] != '$' && data->beg_line[i])
  //        //{
  //        //  node->value[i] = data->beg_line[i];
  //        //  i++;
  //        //}
  //      }
  //      //**i++;
  //      //**char  *dolla;
  //      //**int   len;

  //      //**len = 0;
  //      //**while (ft_acceptable_char(data->beg_line[i]))
  //      //**{
  //      //**  i++;
  //      //**  len++;
  //      //**}
  //      //**if (!(d_quote % 2 == 0 && s_quote % 2 == 1))
  //      //**  dolla = malloc(sizeof(char) * len + 2);
  //      //**else
  //      //**  dolla = malloc(sizeof(char) * len + 1);
  //      //**i = i - len;
  //      //**len = 0;
  //      //**if (d_quote % 2 == 0 && s_quote % 2 == 1)
  //      //**{
  //      //**  dolla[len] = '$';
  //      //**  len++;
  //      //**}
  //      //**while (ft_acceptable_char(data->beg_line[i]))
  //      //**{
  //      //**  dolla[len] = data->beg_line[i];
  //      //**  i++;
  //      //**  len++;
  //      //**}
  //      //**dolla[i] = 0;
  //      //**if (!(d_quote % 2 == 0 && s_quote % 2 == 1))
  //      //**{
  //      //**  while (ft_strncmp(trav_env->sec, dolla, i) && trav_env->next != NULL)
  //      //**    trav_env = trav_env->next;
  //      //**  if (!ft_strncmp(trav_env->sec, dolla, i))
  //      //**  {
  //      //**    free(dolla);
  //      //**    dolla = ft_strdup(trav_env->value);
  //      //**  }
  //      //**  else
  //      //**  {
  //      //**    free(dolla);
  //      //**    dolla = ft_strdup(" ");
  //      //**  }
  //      //**}
  //      //**trav_env = data->l_env;
  //      //**len = 0;
  //      //**while (dolla[len])
  //      //**{
  //      //**  node->value[j] = dolla[len];
  //      //**  j++;
  //      //**  len++;
  //      //**}
  //      //**dolla = NULL;
  //      while (data->beg_line[i] == '\"' || data->beg_line[i] == '\'')
  //      {
  //        if (data->beg_line[i] == '\'')
  //        {
  //          //if (s_quote % 2 == 0)
  //          if (d_quote % 2 == 0)
  //          {
  //            i++; 
  //            s_quote++;
  //          }
  //          else if (d_quote % 2 == 1)
  //          {
  //            s_quote++;
  //            node->value[j] = data->beg_line[i];
  //            i++;
  //            j++;
  //          }
  //          //i++; 
  //          //s_quote++;
  //        }
  //        else if (data->beg_line[i] == '\"')
  //        {
  //          if (s_quote % 2 == 0)
  //          {
  //            i++;
  //            d_quote++;
  //          }
  //          else
  //          {
  //            d_quote++;
  //            node->value[j] = data->beg_line[i];
  //            i++;
  //            j++;
  //          }
  //        }
  //      }
  //    }
  //    //****
  //    while (data->beg_line[i] == '\'' || data->beg_line[i] == '\"')
  //    {
  //      if (data->beg_line[i] == '\'')
  //      {
  //        if (d_quote % 2 == 0)
  //        {
  //          i++; 
  //          s_quote++;
  //        }
  //        else if (d_quote % 2 == 1)
  //        {
  //          s_quote++;
  //          node->value[j] = data->beg_line[i];
  //          i++;
  //          j++;
  //        }
  //        //i++; 
  //        //s_quote++;
  //      }
  //      else if (data->beg_line[i] == '\"')
  //      {
  //        if (s_quote % 2 == 0)
  //        {
  //          i++;
  //          d_quote++;
  //        }
  //        else
  //        {
  //          d_quote++;
  //          node->value[j] = data->beg_line[i];
  //          i++;
  //          j++;
  //        }
  //      }
  //    }
  //    if (&data->beg_line[i + 1] == &data->n_line[0])
  //      break ;
  //    if (data->beg_line[i] != '$')
  //    {
  //      node->value[j] = data->beg_line[i];
  //      i++;
  //      j++;
  //    }
  //  }
  //  data->beg_line = &data->beg_line[i];
  //  node->value[j] = 0;
  //}


  //if (typ == D_QUOT || typ == S_QUOT)
  //{
  //}
  else if (typ == DOLLA)
  {
    //here change the value of dollar sign with it's value in the env
    //node->value = malloc(sizeof(char) * );
    int i;
    int j;

    i = 0;
    j = 0;
    //here do $? let it so i can show the value in echo
    node->value = malloc(sizeof(char) * data->i_line + 1);
    if (data->beg_line[i] == '$')
      i++;
    //fix here
    while (&data->beg_line[i] != & data->n_line[0])
    {
      node->value[j] = data->beg_line[i];
      i++;
      j++;
    }
    node->value[j] = 0;
    data->beg_line = &data->beg_line[i];
    //and check if there another $ to replace it with a code
    while (ft_strncmp(trav_env->sec, node->value, data->i_line) && trav_env->next != NULL)
      trav_env = trav_env->next;
    //if empty
    if (!ft_strncmp(trav_env->sec, node->value, data->i_line))
    {
      free(node->value);
      node->value = ft_strdup(trav_env->value);
    }
    else
    {
      free(node->value);
      node->value = ft_strdup(" ");
    }
    //if (!trav_env)
    //  node->value = ft_strdup(" ");
    //else if (ft_strncmp(trav_env->sec, node->value, data->i_line))
    //{
    //  node->value = ft_strdup(trav_env->value);
    //}
    //data->beg_line = &data->beg_line[i];
    //node->value = ft_strdup(trav_env->value);
  }
  else
  {
    node->value = malloc(sizeof(char) * data->i_line + 1);
    if (!node->value)
      return ;
    i = 0;
    //here is the problem cuz we cmp between indexes ? cmp the address
    //while (data->beg_line[i] != data->n_line[0])
    while (&data->beg_line[i] != &data->n_line[0])
    {
      node->value[i] = data->beg_line[i];
      i++;
    }
    data->beg_line = &data->beg_line[i];
    node->value[i] = 0;
  }
  //*node->value = malloc(sizeof(char) * data->i_line + 1);
  //*if (!node->value)
  //*  return ;
  //*i = 0;
  //*//here is the problem cuz we cmp between indexes ? cmp the address
  //*//while (data->beg_line[i] != data->n_line[0])
  //*while (&data->beg_line[i] != &data->n_line[0])
  //*{
  //*  node->value[i] = data->beg_line[i];
  //*  i++;
  //*}
  //*data->beg_line = &data->beg_line[i];
  //*node->value[i] = 0;
  node->next = NULL;
  //if (check == 0)
  if (data->check == 0)
  {
    trav = data->t_token;
    while (trav->next)
    {
      trav = trav->next;
    }
    trav->next = node;
  }
  if (data->check == 1)
    data->check--;
    //data->t_token->next = node;
  //data->t_token = node;
}

int is_word(t_data *data, char *beg_line)
{
  int   i;
  int   j;
  int   typ;
  //char  sp[] = "<|>'$ ";
  char  sp[] = "<|\">'$ ";

  i = 0;
  typ = WRD;
  //j = 0;
  while (beg_line[i])
  {
    j = 0;
    while (sp[j])
    {
      if (beg_line[0] == sp[j] /*&& i == 0*/)
        return (0);
      else if (beg_line[i] == '\"' || beg_line[i] == '\'')
      {
        if (beg_line[i] == '\"')
          typ = D_QUOT;
        else if (beg_line[i] == '\'')
          typ = S_QUOT;
        j++;
        //i++;
      }
      //else if (beg_line[i] == '$')
      //{
      //  //here for $ dolla change the with it's value
      //  //here send it to the func of is_dolla i will edit it later
      //  //data->typ = DOLLA;
      //}
      else if (beg_line[i] == sp[j] && i > 0)
        break ;
      j++;
    }
    if (beg_line[i] == sp[j])
      break ;
    i++;
  }
  //if (beg_line[i] == 0 && sp[j] == 0)
  //  data->n_line = beg_line;
  //else

  data->typ = typ;
  data->n_line = &beg_line[i];
  //data->beg_line = data->n_line;
  data->i_line = i;
  data->index += i;
  return (1);
}

int is_space(t_data *data, char *n_line)
{
  int i;

  i = 0;
  if (n_line[i] != ' ')
    return (0);
  while (n_line[i] == ' ')
    i++;
  //{
  //  if (n_line[i] != ' ')
  //    break ;
  //  i++;
  //}
  //data->beg_line = data->n_line;
  data->typ = W_SPACE;
  data->n_line = &n_line[i];
  data->i_line = i;
  data->index += i;
  return (1);
  //{
  //  if (n_line[i] != ' ')
  //    return (1);
  //  i++;
  //}
}

//void  add_node_2(t_data *data, t_types typ)
//{
//  t_token *node;
//  int i;
//
//  node = (t_token *) malloc(sizeof(t_token));
//  node->type = typ;
//  node->value = malloc(sizeof(char) * data->i_line + 1);
//  i = 0;
//  while (data->beg_line[i] != data->n_line[0])
//  {
//    node->value[i] = data->beg_line[i];
//    i++;
//  }
//  node->value[i] = 0;
//  node->next = NULL;
//  t_token *trav;
//  trav = data->t_token;
//  while (trav)
//  {
//    trav = trav->next;
//  }
//  trav = node;
//  data->t_token->next = trav;
//  //data->t_token = trav;
//  //data->t_token = node;
//}

int is_pipe(t_data *data, char *n_line)
{
  int i;

  i = 0;
  if (n_line[i] != '|')
    return (0);
  while (n_line[i] == '|')
    i++;
  data->typ = PIPE;
  data->n_line = &n_line[i];
  data->i_line = i;
  data->index += i;
  return (1);
  //if (n_line[i] == '|')
  //{
  //  i++;
  //  data->typ = PIPE;
  //  data->n_line = &n_line[i];
  //  data->i_line = i;
  //  data->index += i;
  //  return (1);
  //}
  //while (n_line[i])
  //{
  //  if ()
  //}
  //data->n_line = &n_line[i];
  //data->i_line = i;
  //data->index += i;
  //return (0);
}

int is_o_redirection(t_data *data, char *n_line)
{
  int i;

  i = 0;
  //if (n_line[i] != '>' && n_line[i] != '<')
  if (n_line[i] != '<')
    return (0);
  while (n_line[i] == '<')
  {
    if (n_line[1] != '<')
    {
      i++;
      data->typ = I_TRNC;
      data->n_line = &n_line[i];
      data->i_line = i;
      data->index += i;
      return (1);
    }
    i++;
  }
  if (n_line[i] != '<')
  {
    data->typ = I_APEND;
    data->n_line = &n_line[i];
    data->i_line = i;
    data->index += i;
    //return (1);
  }
  return (1);
}

int is_i_redirection(t_data *data, char *n_line)
{
  int i;

  i = 0;
  //if (n_line[i] != '>' && n_line[i] != '<')
  if (n_line[i] != '>')
    return (0);
  while (n_line[i] == '>')
  {
    if (n_line[1] != '>')
    {
      i++;
      data->typ = O_TRNC;
      data->n_line = &n_line[i];
      data->i_line = i;
      data->index += i;
      return (1);
    }
    i++;
  }
  if (n_line[i] != '>')
  {
    data->typ = O_APEND;
    data->n_line = &n_line[i];
    data->i_line = i;
    data->index += i;
    //return (1);
  }

  return (1);
  //  i++;
  //if (n_line[i] == '>')
  //{
  //  data->typ = O_TRNC;
  //  if (n_line[++i] == '>')
  //  {
  //    data->typ = O_APEND;
  //    i++;
  //    //return (1);
  //  }
  //  data->n_line = &n_line[i];
  //  data->i_line = i;
  //  data->index += i;
  //  return (1);
  //}
  //else if (n_line[i] == '<')
  //{
  //  data->typ = I_TRNC;
  //  if (n_line[++i] == '<')
  //  {
  //    data->typ = I_APEND;
  //    i++;
  //    //return (1);
  //  }
  //  data->n_line = &n_line[i];
  //  data->i_line = i;
  //  data->index += i;
  //  return (1);
  //}

  //while (n_line[i])
  //{
  //  if (n_line[i] == '>')
  //  {
  //    while (n_line[i])
  //  }
  //  else if (n_line[i] == '<')
  //}
}

int is_s_quote(t_data *data, char *n_line)
{
  int i;
  int j;
  int quote;

  i = 0;
  j = 0;
  quote = 0;
  //i gotta check if the quote are closed here
  if (n_line[i] != '\'')
    return (0);
  //"hey|$cool<<>>"
 

  else if (n_line[i] == '\'')
  {
    i++;
    j++;
    while (n_line[i])
    {
      //here see if there's a space
      if (n_line[i] == '\'')
      {//"ka"ll"we"
        i++;
        while (n_line[i])
        {
          if (n_line[i] == ' ' || n_line[i] == '|' || n_line[i] == '>' || n_line[i] == '<')
          {
            data->typ = D_QUOT;
            data->n_line = &n_line[i];
            data->i_line = i;
            data->index += i;
            return (1);
          }
          i++;
          if (n_line[i] == '\'')
            break ;
        }
      }
      i++;
    }
  }

  //old shiit
  //**if (n_line[i] == '\'')
  //**{
  //**  i++;
  //**  quote++;
  //**  while (n_line[i])
  //**  {
  //**    if (n_line[i] == '\'')
  //**    {
  //**      i++;
  //**      quote++;
  //**      break ;
  //**    }
  //**    i++;
  //**  }
  //**}
  //here error of quote not closed
  if (quote % 2 == 1)
  {
    //printf("error the quote are not closed :/");
    error("error the quote are not closed :/", 1);

  }
  //else if (quote % 2 == 0)
  //{
  //  printf("error the quote are not closed :/");
  //}
  //if (n_line[i] != '\'')
  //  return (0);
  //while (n_line[i] == '\'')
  //  i++;
  data->typ = S_QUOT;
  data->n_line = &n_line[i];
  data->i_line = i;
  data->index += i;
  //{
  //  if (n_line[i] != '\'')
  //  {
  //  }
  //}
  return (1);
}

int is_d_quote(t_data *data, char *n_line)
{
  int i;
  int j;
  int quote;

  i = 0;
  j = 1;
  quote = 0;
  //here check if the "" are closed so u avoid sigfault
  if (n_line[i] != '\"')
    return (0);
  //"hey|$cool<<>>"
  else if (n_line[i] == '\"')
  {
    i++;
    j++;
    while (n_line[i])
    {
      //here see if there's a space
      if (n_line[i] == '\"')
      {//"ka"ll"we"
        i++;
        while (n_line[i])
        {
          if (n_line[i] == ' ' || n_line[i] == '|' || n_line[i] == '>' || n_line[i] == '<')
          {
            data->typ = D_QUOT;
            data->n_line = &n_line[i];
            data->i_line = i;
            data->index += i;
            return (1);
          }
          i++;
          if (n_line[i] == '\"')
            break ;
        }
        //else if (n_line[i] == '$')
        //if (n_line[i])
        //if (n_line[j] != '|' && n_line[j] != '>' && n_line[j] != '<')
        //{

        //}
        //else if (n_line[j] == ' ')
      }
      //if (n_line[i] != ' ' && n_line[i] != '|' && n_line[i] != '>' && n_line[i] != '<')
      //  break ;
      i++;
    }
  }
  //if (n_line[i] == '\"')
  //{
  //  i++;
  //  quote++;
  //  //while (n_line[i] != '\"')
  //  while (n_line[i])
  //  {
  //    if (n_line[i] == '\"')
  //    {
  //      i++;
  //      quote++;
  //      break ;
  //    }
  //    i++;
  //  }
  //}
  //not here cuz the program still keep going and went to run the cmd
  //i will check if the quotes are closed
  //if (quote % 2 == 1)
  //  error("error the quote are not closed :/", 1);

  //while (n_line[i] == '\"')
  //  i++;
  data->typ = D_QUOT;
  data->n_line = &n_line[i];
  data->i_line = i;
  data->index += i;
  return (1);
}

int is_dolla(t_data *data, char *n_line)
{
  int i;

  i = 0;
  //here i should put the value of dolla not the dolla
  if (n_line[i] != '$')
    return (0);
  if (n_line[i] == '$')
  {
    i++;
    //while (n_line[i] != ' ' && n_line[i] != '|' && n_line[i] != '>' && n_line[i] != '<' && n_line[i] != '$' && n_line[i])
    while (n_line[i] != ' ' && n_line[i] != '|' && n_line[i] != '>' && n_line[i] != '<' && n_line[i])
    {
      if (n_line[i] == '$')
      {
        i++;
        break ;
      }
      i++;
    }
  }

  //while (n_line[i] == '$')
  //  i++;

  data->typ = DOLLA;
  data->n_line = &n_line[i];
  data->i_line = i;
  data->index += i;
  return (1);
}

void  tokenizer(t_data *data)
{
  //t_types typ;
  //t_token *node;

  if (data->line[0] == ' ')
    data->beg_line = ft_strchr(data->line, ' ');
  else
    data->beg_line = data->line;
  //printf("%s\n", data->beg_line);
  data->n_line = data->beg_line;
  data->i_line = 0;
  data->index = 0;
  //node_head(data);
  //int i = 1;
  data->check = 1;
  while (data->line[data->index])
  {
    //if (is_word(data, data->beg_line))
    if (is_word(data, data->n_line))
    {
      //typ = WRD;
      //add_node(data, data->typ, i);
      add_node(data, data->typ);
      //if (i == 1)
      //  i--;
      //data->t_token = node;
    }
    //i--;
    if (is_space(data, data->n_line))
    {
      //typ = W_SPACE;
      //add_node(data, data->typ, i);
      add_node(data, data->typ);
      //if (i == 1)
      //  i--;
      //add_node_2(data, typ);
    }
    //still fix pipe fucntion
    if (is_pipe(data, data->n_line))
    {
      //typ = PIPE;
      //add_node(data, data->typ, i);
      add_node(data, data->typ);
      //if (i == 1)
      //  i--;
    }
    //still fix redirection fucntion
    if (is_o_redirection(data, data->n_line))
    {
      //typ = typ;
      add_node(data, data->typ);
      //if (i == 1)
      //  i--;
    }
    if (is_i_redirection(data, data->n_line))
    {
      //typ = typ;
      add_node(data, data->typ);
      //if (i == 1)
      //  i--;
    }
    if (is_s_quote(data, data->n_line))
    {
      add_node(data, data->typ);
      //if (i == 1)
      //  i--;
    }
    //double quote space not count
    if (is_d_quote(data, data->n_line))
    {
      add_node(data, data->typ);
      //if (i == 1)
      //  i--;
    }
    if (is_dolla(data, data->n_line))
    {
      add_node(data, data->typ);
      //if (i == 1)
      //  i--;
    }
    //if (is_pipe(data, data->n_line))
    //while (data->t_token)
    //{
    //  printf("%d\n", data->t_token->type);
    //  printf("%s\n", data->t_token->value);
    //  data->t_token = data->t_token->next;
    //}
  }
  //****
  //here to write the arg that i entred in the nodes
  t_token *trav;

  trav = data->t_token;
  while (trav)
  {
    printf("| %d |\n", trav->type);
    printf("| %s |\n", trav->value);
    printf("\n");
    trav = trav->next;
  }
  //negad linker dial nodes and other fuction of pipe and redirection
}


//int white_spaces(int c)
//{
//  int i;
//  //char  spaces[] = "\t ";
//  
//  i = 0;
//  while (c == 32 || (c >= 9 && c <= 13))
//  {
//
//  }
//}

//char *check_word(char *str)
//{
//  int i;
//  char  *w_end;
//
//  i = 0;
//  while (str[i] != ' ')
//    i++;
//  w_end = &str[i];
//  return (w_end);
//}

//int ft_isword(char *str)
//{
//  int i;
//
//  i = 0;
//  while (str[i] != ' ')
//  {
//    if (!ft_isalnum(str[i]))
//      return (0);
//      //break ;
//    i++;
//    //ft_isalnum(str[i]);
//    //while (ft_isalnum(str[i]))
//    //{
//    //  i++;
//    //}
//    //return (&str[i]);
//    //if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
//    //  i++;
//    //else if (str[i] == '-' || str[i] == '/')
//  }
//  return (1);
//  //return (&str[i]);
//}

//void  tokenizer(t_data *data)
//{
//  int   i;
//  char  *tmp;
//  t_types typ;
//
//  i = 0;
//  //tmp = data->line;
//  if (data->line[0] == ' ')
//    tmp = ft_strchr(data->line, ' ');
//  while (i > 1)
//  {
//    if (ft_isword(data->line))
//    {
//      typ = WRD;
//      add_node(tmp, typ);
//    }
//
//
//
//
//    //if (data->line[i] == 32 || (data->line[i] >= 9 && data->line[i] <= 13))
//    //if (ft_strchr(tmp, ' ')) //this one is out of the while
//      //tmp = data->line; //nothing adress of line in return of strchr
//      //add to node of whitespaces or maybe just ignore the first spaces
//    //else if (data->line[i] == '|')
//      //function of adding node of pipe
//    i++;
//  }
//}
