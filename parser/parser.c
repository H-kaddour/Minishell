/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:32:56 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/04 23:10:00 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  count_cmd(t_data *data)
{
  t_token *trav;
  int     i;
  int     j;

  i = 0;
  j = 0;
  trav = data->t_token;
  while (trav)
  {
    if (trav->type == PIPE && j != 0 && trav->next)
      i++;
    trav = trav->next;
    j++;
  }
  return (i);
}

static void allocate_cmd_node(t_data *data)
{
  int   i;
  int   len;
  t_cmd *head;
  t_cmd *node;

  i = 1;
  len = count_cmd(data) + 1;
  head = malloc(sizeof(t_cmd));
  head->cmd = 0;
  head->f_in = 0;
  head->f_out = 1;
  head->redirect = 0;
  head->next = 0;
  data->v_cmd = head;
  while (i < len)
  {
    node = malloc(sizeof(t_cmd));
    node->cmd = 0;
    node->f_in = 0;
    node->f_out = 1;
    node->redirect = 0;
    node->next = 0;
    head->next = node;
    head = node;
    i++;
  }
}

static void allocate_red_node(t_data *data, int red_len)
{
  int i;
  t_red *head;
  t_red *node;

  i = 1;
  if (red_len != 0)
  {
    head = malloc(sizeof(t_red));
    head->typ = 0;
    head->file = 0;
    head->determiner = 0;
    head->next = 0;
    data->trav_cmd->redirect = head;
  }
  while (i < red_len)
  {
    node = malloc(sizeof(t_red));
    node->typ = 0;
    node->file = 0;
    node->determiner = 0;
    node->next = 0;
    head->next = node;
    head = node;
    i++;
  }
}

void  parsing_get_len_alloc_cmd_arr(t_data *data, int *len, int *red_len)
{
  while (data->trav)
  {
    if (data->trav->type == WRD || data->trav->type == D_QUOT \
        || data->trav->type == S_QUOT || data->trav->type == DOLLA)
    {
      *(len) += 1;
      data->trav = data->trav->next;
    }
    else if (data->trav->type == W_SPACE)
      data->trav = data->trav->next;
    else if (data->trav->type == O_TRNC || data->trav->type == O_APEND \
        || data->trav->type == I_TRNC || data->trav->type == I_APEND)
    {
      if (data->trav->next->type == W_SPACE)
        data->trav = data->trav->next->next->next;
      else
        data->trav = data->trav->next->next;
      *(red_len) += 1;
    }
    else if (data->trav->type == PIPE)
      break ;
  }
}

t_token *parsing_alloc_red_space(t_data *data, t_token *trav, int *chk, t_red *trav_red)
{
  trav_red->typ = trav->type;
  if (trav->type != I_APEND)
    trav_red->file = ft_strdup(trav->next->next->value);
  else
  {
    trav_red->determiner = ft_strdup(trav->next->next->value);
    if (*chk != 0)
      close(data->hrdoc_fd[0]);
    heredoc_implement(data, trav_red->determiner);
    if (data->chk_hrdoc_exit == 1)
      return (trav);
    *(chk) = 1;
  }
  trav = trav->next->next->next;
  return (trav);
}

t_token *parsing_alloc_red_no_space(t_data *data, t_token *trav, int *chk, t_red *trav_red)
{
  trav_red->typ = trav->type;
  if (trav->type != I_APEND)
    trav_red->file = ft_strdup(trav->next->value);
  else
  {
    trav_red->determiner = ft_strdup(trav->next->value);
    if (*chk != 0)
      close(data->hrdoc_fd[0]);
    heredoc_implement(data, trav_red->determiner);
    if (data->chk_hrdoc_exit == 1)
      return (trav);
    *(chk) = 1;
  }
  trav = trav->next->next;
  return (trav);
}

int get_cmd_parsing_helper(t_data *data, t_token **trav, t_red **trav_red, int *i)
{
  int chk;

  chk = 0;
  if (trav[0]->type == WRD || trav[0]->type == D_QUOT \
      || trav[0]->type == S_QUOT || trav[0]->type == DOLLA)
  {
    data->trav_cmd->cmd[*i] = ft_strdup(trav[0]->value);
    *trav = trav[0]->next;
    *(i) += 1;
  }
  else if (trav[0]->type == W_SPACE)
    *trav = trav[0]->next;
  else if (trav[0]->type == O_TRNC || trav[0]->type == O_APEND \
      || trav[0]->type == I_TRNC || trav[0]->type == I_APEND)
  {
    if (trav[0]->next->type == W_SPACE)
      *trav = parsing_alloc_red_space(data, *trav, &chk, *trav_red);
    else
      *trav = parsing_alloc_red_no_space(data, *trav, &chk, *trav_red);
    if (data->chk_hrdoc_exit == 1)
      return (1);
    *trav_red = trav_red[0]->next;
  }
  return (0);
}

static void get_cmd_parsing(t_data *data)
{
  t_token *trav;
  t_red   *trav_red;
  int     red_len;
  int     cmd_len;
  int     i;

  i = 0;
  red_len = 0;
  cmd_len = 0;
  trav = data->trav;
  parsing_get_len_alloc_cmd_arr(data, &cmd_len, &red_len);
  data->trav_cmd->cmd = malloc(sizeof(char *) * cmd_len + 1);
  allocate_red_node(data, red_len);
  trav_red = data->trav_cmd->redirect;
  while (trav)
  {
    if (trav->type != PIPE)
    {
      if (get_cmd_parsing_helper(data, &trav, &trav_red, &i))
        return ;
    }
    else if (trav->type == PIPE)
      break ;
  }
  data->trav_cmd->cmd[i] = 0;
  data->trav_cmd = data->trav_cmd->next;
}

void  parser(t_data *data)
{
  allocate_cmd_node(data);
	data->chk_hrdoc_exit = 0;
  data->trav_cmd = data->v_cmd;
  data->trav = data->t_token;
  while (data->trav)
  {
    get_cmd_parsing(data);
    if (data->chk_hrdoc_exit == 1)
    {
      data->error_lexer = 1;
      return ;
    }
    if (!data->trav)
      break ;
    else if (data->trav->type == PIPE)
      data->trav = data->trav->next;
  }
}
