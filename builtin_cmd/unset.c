/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:18:49 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/04 10:17:33 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	find_that_element(t_data *data, char *elem)
{
	t_env	*trav;
	t_env	*trav_prev;

	trav = data->l_env;
	trav_prev = data->l_env;
	while (ft_strcmp(trav->sec, elem) && trav->next)
	{
		trav_prev = trav;
		trav = trav->next;
	}
	if (!ft_strcmp(trav->sec, elem))
	{
		trav_prev->next = trav->next;
		free(trav->sec);
		free(trav->value);
		free(trav);
	}
	else
		return ;
}

void	unset_cmd(t_data *data, t_cmd *trav_c)
{
	int		i;
	//t_cmd	*trav_c;

	i = 1;
	//trav_c = data->v_cmd;
	if (!trav_c->cmd[1])
		return ;
	while (trav_c->cmd[i])
	{
		find_that_element(data, trav_c->cmd[i]);
		i++;
	}
}
