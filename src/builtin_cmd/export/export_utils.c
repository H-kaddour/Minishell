/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 02:54:40 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 21:39:32 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*before_equal(char *cmd)
{
	int		i;
	int		hold;
	char	*chk;

	i = 0;
	hold = ft_strcspn(cmd, "=");
	if (cmd[hold - 1] == '+')
		hold--;
	chk = malloc(sizeof(char) * hold + 1);
	if (!chk)
		error_malloc();
	while (i < hold)
	{
		chk[i] = cmd[i];
		i++;
	}
	chk[i] = 0;
	return (chk);
}

int	if_exist_or_not(t_data *data, char *cmd)
{
	t_env	*trav;
	char	*ptr;
	int		chk;

	chk = 0;
	ptr = cmd;
	if (check_if_equal_or_wrd(cmd))
	{
		ptr = before_equal(cmd);
		chk = 1;
	}
	trav = getenv_addr(data, ptr);
	if (chk)
		free(ptr);
	if (trav)
		return (0);
	else
		return (1);
}

int	only_accepted_char(char *cmd, int hold)
{
	int	i;

	i = 1;
	if (ft_isdigit(cmd[0]))
		return (1);
	while (i < hold)
	{
		if (!ft_isdigit(cmd[i]) && !ft_isalnum(cmd[i]) \
				&& cmd[i] != '+' && cmd[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	check_export_error_helper(t_data *data, char *cmd, int hold)
{
	int	i;

	i = 0;
	if (cmd[hold - 1] == '+')
		hold--;
	while (i < hold)
	{
		if (cmd[i] == '+')
			return (1);
		i++;
	}
	if (cmd[hold] == '+')
		data->chk_export_plus = 1;
	return (0);
}

int	check_export_error(t_data *data, char *cmd)
{
	int	hold;
	int	i;

	i = 0;
	hold = ft_strcspn(cmd, "=");
	if (only_accepted_char(cmd, hold))
		return (1);
	if (cmd[i] == '=' || cmd[i] == '+')
		return (1);
	while (cmd[i] != '=' && cmd[i])
		i++;
	if (cmd[i] == 0)
	{
		i = 0;
		while (cmd[i] != '+' && cmd[i])
			i++;
		if (cmd[i] == 0)
			return (0);
		else
			return (1);
	}
	if (check_export_error_helper(data, cmd, hold))
		return (1);
	return (0);
}
