/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:22:04 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/02 03:40:28 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_cd(t_data *data, char *msg)
{
	data->chk_dolla = 1;
	printf("%s\n", msg);
}

void	cd_cmd(t_data *data)
{
	t_cmd	*node;

	node = data->v_cmd;
	if (node->cmd[1])
	{
		if (node->cmd[1][0] == '-')
		{
			cd_between_pwd_and_oldpwd(data, node->cmd[1]);
			return ;
		}
	}
	cd_everywhere_at_once(data, node->cmd[1]);
}
