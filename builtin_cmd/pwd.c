/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:22:53 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/01 09:35:01 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  pwd_cmd(t_data *data)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, "PWD") && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, "PWD"))
    printf("%s\n", trav->value);
  else
    printf("PWD = %s\n", data->pwd_of_mysys);
}
