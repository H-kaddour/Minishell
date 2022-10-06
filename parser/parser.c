/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:32:56 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/06 10:18:16 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *parsing_alloc_red_space(t_data *data, t_token *trav, \
    int *chk, t_red *trav_red)
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

t_token *parsing_alloc_red_no_space(t_data *data, t_token *trav, \
    int *chk, t_red *trav_red)
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

int get_cmd_parsing_helper(t_data *data, t_token **trav, \
    t_red **trav_red, int *i)
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
  if (!data->trav_cmd->cmd)
    error_malloc();
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
