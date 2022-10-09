/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:00:06 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/09 11:11:51 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*init_var_get_cmd_parsing(t_data *data, int *i, int *red, int *cmd)
{
	*(i) = 0;
	*(red) = 0;
	*(cmd) = 0;
	data->chk_hrdc_cls = 0;
	data->hrdoc_fd[1] = 0;
	return (data->trav);
}

int	count_cmd(t_data *data)
{
	t_token	*trav;
	int		i;
	int		j;

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

void	parsing_get_len_alloc_cmd_arr(t_data *data, int *len, int *red_len)
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
