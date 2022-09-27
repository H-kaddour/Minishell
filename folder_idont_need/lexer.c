/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:13:45 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/04 09:41:38 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void  check_wrd(char *str)
//{
//  int i;
//
//  i = 0;
//  while (str[i])
//  {
//    i++;
//  }
//}

//void  check_pipe(char *str)
//{
//  int i;
//
//  i = 0;
//  while (str[i])
//  {
//    i++;
//  }
//}

//void  check_error(t_data *data)
//{
//  t_token *trav;
//
//  trav = data->t_token;
//  while (trav)
//  {
//    //if (trav->type == WRD)
//    //  check_wrd(trav->value);
//    //else if (trav->type == W_SPACE)
//    if (trav->type == PIPE)
//      check_pipe();
//    else if (trav->type == S_QUOT)
//    else if (trav->type == D_QUOT)
//    else if (trav->type == DOLLA)
//    else if (trav->type == O_TRNC)
//    else if (trav->type == O_APEND)
//    else if (trav->type == I_TRNC)
//    else if (trav->type == I_APEND)
//    trav = trav->next;
//  }
//}

void  error(char *msg, int check)
{
  if (check == 0)
  {
    printf("minishell: syntax error no token: %s", msg);
    nl();
  }
  else if (check == 1)
  {
    printf("%s\n", msg);
    nl();
  }
  else if (check == 2)
  {
    printf("minishell: %s: command not found 'space'\n", msg);
    nl();
  }
  //if (check == 0)
  //{
  //  ft_putstr_fd(msg, 0);
  //  sig_c(SIGINT);
  //  //exit(0);
  //}
  //else if (check == 1)
  //  ft_putstr_fd(msg, 0);
  //else
  //  exit(0);
}

//not working
//void  variable_dolla(t_data *data, char *str)
//{
//  int i;
//  int j;
//  char  *var; //dalla sign variable allocate here.
//
//  i = 0;
//  j = 0;
//  while (str[i] != '=')
//    i++;
//  var = malloc(sizeof(char) * ft_strlen(&str[i]));
//  //the if down below take it off
//  if (str[i] == '=')
//  {
//    //var = malloc(sizeof(char) * ft_strlen(&str[i]));
//    while (str[i])
//    {
//      var[j] = str[i];
//      j++;
//      i++;
//    }
//    var[j] = 0;
//  }
//  data->var = var;
//}

void  check_dolla(char *str)
{
  int i;

  i = 0;
  //$ ok=hhic space at first
  if (str[i] == ' ')
    error("This is not a var", 1);
  //check error if it not a word and = not exist
  //while (str[i])
  //{

  //}
}

void  pipe_grammar(t_data *data, t_token *pipe)
{
  //t_token *trav;

  //data->trav_p = data->t_token;
  if (data->trav_p->type == PIPE)
    error("Wrong syntax | in first with no arg begind", 1);
  //if pipe is in the first node so its sigfault cuz looping and reach NULL
  if (data->trav_p->type != PIPE)
  {
    while (data->trav_p->next->type != pipe->type)
      data->trav_p = data->trav_p->next;
  }
  if (data->trav_p->type != W_SPACE && data->trav_p->type != WRD &&\
      data->trav_p->type != S_QUOT && data->trav_p->type != D_QUOT)
    //only pipe and all others are allowed
    error("Wrong syntax \"wrd or space or quotes\" |", 1);
  data->trav_p = data->trav_p->next;
  if (data->trav_p->next == NULL)
    error("Wrong syntax | \"wrd or space\"", 1);
  data->trav_p = data->trav_p->next;
  if (data->trav_p != NULL)
  {
    if (data->trav_p->type != W_SPACE && data->trav_p->type != WRD &&\
        data->trav_p->type != O_TRNC && data->trav_p->type != O_APEND &&\
        data->trav_p->type != I_TRNC && data->trav_p->type != I_APEND)
      error("Wrong syntax | \"wrd or space\"", 1);
  }
  //  if (data->trav_p->type)
  //{
  //  if (data->trav_p->type)
  //  data->trav_p = data->trav_p->next;
  //}
}

int check_pipes(char *str)
{
  int i;

  i = 1;
  if (str[i] == '|')
    return (1);
  //else if (str[i] == 0)
  return (0);
}

int check_redirection(char *str)
{
  int i;

  i = 2;
  if (str[i] == '>' || str[i] == '<')
    return (1);
  return (0);
}

int check_dalla(char *str)
{
  int i;

  i = 1;
  if (str[i] == '$')
    return (1);
  return (0);
}

//int check_quotes(t_token *quote)
//{
//  int i;
//  
//  i = 0;
//  //while (quote)
//  //{
//    if (quote->type == D_QUOT)
//    {
//      while (quote->value[i])
//      {
//        i++;
//      }
//      //i++;
//    }
//    //quote = quote->next;
//  //}
//  if (i % 2 == 0)
//    return (0);
//  //else if (i % 2 == 1)
//  //  return (1);
//  else
//    return (1);
//}

void  check_node_error(t_data *data)
{
  t_token *trav;

  trav = data->t_token;
  while (trav)
  {
    if (check_pipes(trav->value))
    {
      error(trav->value, 0);
      break ;
    }
    else if (check_redirection(trav->value))
    {
      error(trav->value, 0);
      break ;
    }
    else if (check_dalla(trav->value))
    {
      error(trav->value, 0);
      break ;
    }
    //else if (check_quotes(trav))
    //else if (trav->type == D_QUOT)
    //{
    //  if (check_quotes(trav))
    //  {
    //    error(trav->value, 0);
    //    break ;
    //  }
    //}
    //check other like 
    trav = trav->next;
  }
}

int typ_cmp(t_types t1, t_types t2)
{
  if (t1 == t2)
    return (1);
  else
    return (0);
}

void  ot_grammar(t_data *data, t_token *ot)
{
  //t_token *trav;

  //trav = data->t_token;
  if (data->trav_r->type != ot->type)
  {
    while (data->trav_r->next->type != ot->type)
      data->trav_r = data->trav_r->next;
  }
  if (data->trav_r->type != W_SPACE && data->trav_r->type != WRD &&\
      data->trav_r->type != S_QUOT && data->trav_r->type != D_QUOT && data->trav_r->type != PIPE)
    error("Wrong syntax \"wrd or space or quotes\" >", 1);
  data->trav_r = data->trav_r->next;
  if (data->trav_r->next == NULL)
    error("Wrong syntax \"wrd or space or quotes\" >", 1);
  data->trav_r = data->trav_r->next;
  if (data->trav_r != NULL)
  {
    if (data->trav_r->type != WRD && data->trav_r->type != W_SPACE)
      error("Wrong syntax > \"wrd or space\"", 1);
    if (data->trav_r->type == W_SPACE)
    {
      if (data->trav_r->next->type != WRD)
        error("Wrong syntax > and space \"wrd file\"", 1);
    }
  }
  //here check if the file is not exist so you can make it
}

//fix exit i have to write it two time
void  dolla_grammar(t_data *data, t_token *dolla)
{
  t_token *trav;
  int check;

  check = 0;
  trav = data->t_token;
  if (trav->type != dolla->type)
  {
    if (trav->type == D_QUOT || trav->type == S_QUOT)
      check++;
    while (trav->next->type != dolla->type)
      trav = trav->next;
  }
  //check 1 means there's "" '' so shiit change
  if (check == 0)
  {
    if (trav->type == PIPE)
    {
      error("Wrong syntax \"pipe\" $", 1);
      //return ;
    }
  }
  //else
  //{

  //}
  //if (trav->type != W_SPACE && trav->type != )
  //  error("Wrong syntax \"space\" $", 1);
  ////trav = trav->next;
  //if (trav->next == NULL)
  //  error("Wrong syntax $ \" word \"", 1);
  //segfault if NULL cuz it keep going
  //else
  //{
  if(trav->next == NULL)
    return ;
  if (trav->next != NULL)
  {
    trav = trav->next;
    if (check == 0)
    {
      if (trav->type == PIPE || trav->type == O_TRNC || trav->type == I_TRNC ||\
          trav->type == O_APEND || trav->type == I_APEND)
        error("Wrong syntax $ \" no pipe and directions \"", 1);
    }
    //else
    //{
    //}
    //if (trav->type != WRD)
    //  error("Wrong syntax $ \" word \"", 1);
  }
  //}
}

//void  lexer(t_data *data)
//{
//  //int   i;
//  t_token *trav;
//
//  //i = 0;
//  trav = data->t_token;
//  data->trav_p = data->t_token;
//  data->trav_r = data->t_token;
//  check_node_error(data);
//  while (trav)
//  {
//    //check an error if "" are not close
//    //if (!ft_strncmp(trav->type, PIPE, 1))
//    //break in every fucntion so to not have a lot of error
//    if (typ_cmp(trav->type, PIPE))
//      pipe_grammar(data, trav);
//    else if (typ_cmp(trav->type, O_TRNC))
//      ot_grammar(data, trav);
//    else if (typ_cmp(trav->type, O_APEND))
//      ot_grammar(data, trav);
//    else if (typ_cmp(trav->type, I_TRNC))
//      ot_grammar(data, trav);
//    else if (typ_cmp(trav->type, I_APEND))
//      ot_grammar(data, trav);
//    else if (typ_cmp(trav->type, DOLLA))
//      dolla_grammar(data, trav);
//    //else if (typ_cmp(trav->type, D_QUOT))
//    //  d_quot_grammar(data, trav);
//    //this code for $ variable
//    //i++;
//    //segfaul when $ is not use like variavle only
//    //if (!ft_strncmp(trav->value, "$", 1))
//    //{
//    //  trav = trav->next;
//    //  check_dolla(trav->value);
//    //  variable_dolla(data, trav->value);
//    //  printf("%s\n", data->var);
//    //  //printf("%d\n", i);
//    //  //printf("%s\n", trav->value);
//    //}
//    //data->trav_p = trav;
//    trav = trav->next;
//  }
//}
