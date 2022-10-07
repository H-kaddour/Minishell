/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:38:38 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 10:57:06 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exit_stat(char *cmd, int stat, int chk)
{
	printf("exit\n");
	if (chk == 1)
		printf("minishell: exit: %s: too many arguments\n", cmd);
	exit(stat);
}

static int	check_nbr(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

void	exit_cmd(t_data *data, t_cmd *trav)
{
	if (!trav->cmd[1])
		exit_stat(0, 0, 0);
	else
	{
		if (check_nbr(trav->cmd[1]))
		{
			if (!trav->cmd[2])
				exit_stat(0, 255, 0);
			else
			{
				data->chk_dolla = 1;
				printf("exit\n");
				printf("minishell: exit: too many arguments\n");
			}
		}
		else
			exit_stat(trav->cmd[1], 255, 1);
	}
}
