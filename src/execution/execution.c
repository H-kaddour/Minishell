/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:01:19 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 15:44:06 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	size_cmd(t_data *data)
{
	data->size_cmd = 0;
	data->trav_cmd = data->v_cmd;
	while (data->trav_cmd)
	{
		data->size_cmd++;
		data->trav_cmd = data->trav_cmd->next;
	}
}

void	execution(t_data *data)
{
	size_cmd(data);
	if (data->size_cmd == 1)
	{
		if (!check_redirection(data, data->v_cmd))
		{
			if (data->v_cmd->cmd[0])
				run_one_cmd(data);
		}
		if (data->chk_redct_exist == 1)
		{
			if (data->v_cmd->f_in > 0)
				close(data->v_cmd->f_in);
			if (data->v_cmd->f_out > 1)
				close(data->v_cmd->f_out);
		}
	}
	else
		if (pipeline(data) == -3)
		{
			int status;
			kill(waitpid(-1, &status, 0), 9);
			return ;
		}
}
