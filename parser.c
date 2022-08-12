/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:42:42 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/12 12:37:00 by hkaddour         ###   ########.fr       */
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

//void  add_node(t_data *data, t_types typ, int check)
void  add_node(t_data *data, t_types typ)
{
  t_token *node;
  t_token *trav;
  int i;

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
  char  sp[] = "<|\">'$ ";

  i = 0;
  //j = 0;
  while (beg_line[i])
  {
    j = 0;
    while (sp[j])
    {
      if (beg_line[0] == sp[j] /*&& i == 0*/)
        return (0);
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
  data->typ = WRD;
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
  int quote;

  i = 0;
  quote = 0;
  //i gotta check if the quote are closed here
  if (n_line[i] != '\'')
    return (0);
  //"hey|$cool<<>>"
  if (n_line[i] == '\'')
  {
    i++;
    quote++;
    while (n_line[i])
    {
      if (n_line[i] == '\'')
      {
        i++;
        quote++;
        break ;
      }
      i++;
    }
  }
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
  int quote;

  i = 0;
  quote = 0;
  //here check if the "" are closed so u avoid sigfault
  if (n_line[i] != '\"')
    return (0);
  //"hey|$cool<<>>"
  if (n_line[i] == '\"')
  {
    i++;
    quote++;
    //while (n_line[i] != '\"')
    while (n_line[i])
    {
      if (n_line[i] == '\"')
      {
        i++;
        quote++;
        break ;
      }
      i++;
    }
  }
  //not here cuz the program still keep going and went to run the cmd
  if (quote % 2 == 1)
    error("error the quote are not closed :/", 1);
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
  if (n_line[i] != '$')
    return (0);
  while (n_line[i] == '$')
    i++;
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
  //t_token *trav;

  //trav = data->t_token;
  //while (trav)
  //{
  //  printf("| %d |\n", trav->type);
  //  printf("| %s |\n", trav->value);
  //  printf("\n");
  //  trav = trav->next;
  //}
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
