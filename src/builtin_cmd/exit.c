/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:38:38 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/10 14:22:22 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exit_stat(char *cmd, int stat, int chk)
{
	printf("exit\n");
	if (chk == 1)
		printf("minishell: exit: %s: numeric argument required\n", cmd);
	//here i should free
	exit(stat);
}

static int	check_nbr(char *arg)
{
	if (*arg == '-')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

static int	check_if_ll(char *nbr)
{
	int		i;
	int		j;
	char	*ll;

	if (nbr[0] == '-')
	{
		if (ft_strlen(nbr) < 20)
			return (0);
		else if (ft_strlen(nbr) > 20)
			return (1);
		i = 1;
		ll = LL_MIN;
	}
	else
	{
		if (ft_strlen(nbr) < 19)
			return (0);
		else if (ft_strlen(nbr) > 19)
			return (1);
		i = 0;
		ll = LL_MAX;
	}
	if (nbr[i] < '9')
		return (0);
	i++;
	j = i;
	while (nbr[i])
	{
		if (nbr[i] < ll[j])
			return (0);
		else if (nbr[i++] > ll[j++])
			return (1);
	}
	return (0);
}

static void	exit_number(char *nbr)
{
	int		nb_exit;

	nb_exit = ft_atoi(nbr);
	if (check_if_ll(nbr))
		exit_stat(nbr, 255, 1);
	exit_stat(0, (nb_exit % 256), 0);
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
				exit_number(trav->cmd[1]);
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
