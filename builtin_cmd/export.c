/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:52:18 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/23 18:50:14 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int len_of_args(char **cmd)
{
  int i;

  i = 0;
  while (cmd[i])
    i++;
  return (i);
}

void  print_env_of_export(t_env *env)
{
  while (env)
  {
    if (!env->value)
      printf("declare -x %s\n", env->sec);
    else
      printf("declare -x %s=\"%s\"\n", env->sec, env->value);
    env = env->next;
  }
}

void  alloc_node_of_export(t_env *lst, int len)
{
  int   i;
  t_env *node;

  i = 0;
  while (i < len)
  {
    node = node_allocate();
    lst->next = node;
    lst = node;
    i++;
  }
}

int check_if_equal_or_wrd(char *cmd)
{
  int i;

  i = 0;
  while (cmd[i])
  {
    if (cmd[i] == '=')
      return (1);
    i++;
  }
  return (0);
}

int dup_opt_wrd(t_data *data, t_env *env, char *cmd)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, cmd) && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, cmd))
    return (0);
  else
    env->sec = ft_strdup(cmd);
  return (1);
}

int check_existence(t_data *data, char *cmd, int hold, t_env *env)
{
  int   i;
  char  *chk;
  t_env *trav;

  i = 0;
  trav = data->l_env;
  chk = malloc(sizeof(char) * hold + 1);
  while (i < hold)
  {
    chk[i] = cmd[i];
    i++;
  }
  chk[i] = 0;
  //take_off_the_equalsign(hold,);
  //here problem of new node that i add are empty 0 and strcmp doesnt return shiit i have to fix it 
  while (ft_strcmp(trav->sec, chk) && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, chk))
  {
    if (!ft_strcmp(trav->value, &cmd[++hold]))
      return (1);
    else
    {
      trav->value = ft_strdup(&cmd[++hold]);
      //env->value = ft_strdup(&cmd[++hold]);
    }
    return (1);
  }
  return (0);
}

int dup_opt_equal(t_data *data, t_env *env, char *cmd)
{
  int   i;
  int   hold;

  i = 0;
  //hold = &cmd[ft_strcspn(cmd, "=")];
  hold = ft_strcspn(cmd, "=");
  if (check_existence(data, cmd, hold, env) == 1)
    return (0);

  //while (&cmd[i] != &hold[0])
  env->sec = malloc(sizeof(char) * hold + 1);
  while (i < hold)
  {
    env->sec[i] = cmd[i];
    i++;
  }
  env->sec[i] = 0;
  hold++;
  i = 0;
  env->value = malloc(sizeof(char) * ft_strlen(&cmd[hold]) + 1);
  while (cmd[hold])
    env->value[i++] = cmd[hold++];
  env->value[i] = 0;
  return (1);
}

char  *before_equal(char *cmd)
{
  int   i;
  int   hold;
  char  *chk;

  i = 0;
  if (!check_if_equal_or_wrd(cmd))
    return (cmd);
  else
  {
    hold = ft_strcspn(cmd, "=");
    chk = malloc(sizeof(char) * hold + 1);
    while (i < hold)
    {
      chk[i] = cmd[i];
      i++;
    }
    chk[i] = 0;
  }
  return (chk);
}

void  if_exist_or_not(t_data *data, char **cmd, int *len)
{
  int   i;
  t_env  *trav;

  *(len) = 1;
  trav = data->l_env;
  while (trav)
  {
    i = 0;
    while (ft_strcmp(trav->sec, before_equal(cmd[i])) && cmd[i + 1])
      i++;
    if (!ft_strcmp(trav->sec, before_equal(cmd[i])))
      *(len) += 1;
      //*(len)++;
    trav = trav->next;
  }
}

void  export_cmd(t_data *data)
{
  int   i;
  int   len;
  int   chk;
  t_env *trav_e;
  t_cmd *trav_c;

  i = 1;
  trav_e = data->l_env;
  trav_c = data->v_cmd;
  len = len_of_args(trav_c->cmd) - 1;
  if (!len)
    print_env_of_export(trav_e);
  else
  {
    if_exist_or_not(data, &trav_c->cmd[i], &len);
    while (trav_e->next)
      trav_e = trav_e->next;
    alloc_node_of_export(trav_e, len);
    trav_e = trav_e->next;
    while (trav_c->cmd[i] && trav_e)
    {
      if (!check_if_equal_or_wrd(trav_c->cmd[i]))
        chk = dup_opt_wrd(data, trav_e, trav_c->cmd[i]);
      else
        chk = dup_opt_equal(data, trav_e, trav_c->cmd[i]);
      i++;
      if (chk == 1)
        trav_e = trav_e->next;
    }
  }
  //here func should sort the env
  //sort_env();
}

//we have two option export the cmd and options are wrd || wrd=wrd
//wrd only just enter it with null in the value
//wrd=wrd get the sec and value by spliting it with =
//but first have to get the end of env to start entering args
//i have to loop for export args and = split and wrd not
//alloc a node and enter args and go to next one 
//lastly but not least sort the env uppercasse then lowercase
//export only should print the env
//EXPORT if is big dirha sghira
