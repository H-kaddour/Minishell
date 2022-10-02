/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 01:44:45 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/02 04:25:19 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dup_opt_equal_helper(t_env **env, char *cmd, int *hold)
{
	int	i;

	i = 0;
	while (i < *hold)
	{
		env[0]->sec[i] = cmd[i];
		i++;
	}
	env[0]->sec[i] = 0;
	if (cmd[*hold] == '+')
		*(hold) += 2;
	else
		*(hold) += 1;
}

int	check_existence_helper(t_data *data, char *cmd, char *chk, int hold)
{
	t_env	*trav;
	char	*n_cmd;

	trav = getenv_addr(data, chk);
	if (trav)
	{
		if (data->chk_export_plus == 1)
		{
			hold += 2;
			n_cmd = &cmd[hold];
			trav->value = ft_strjoin(trav->value, n_cmd);
		}
		else
		{
			n_cmd = &cmd[++hold];
			trav->value = ft_strdup(n_cmd);
		}
		return (1);
	}
	return (0);
}

int	check_existence(t_data *data, char *cmd, int hold, t_env *env)
{
	int		i;
	char	*chk;

	i = 0;
	chk = malloc(sizeof(char) * hold + 1);
	if (!chk)
		return (0);
	while (i < hold)
	{
		chk[i] = cmd[i];
		i++;
	}
	chk[i] = 0;
	if (check_existence_helper(data, cmd, chk, hold))
		return (1);
	return (0);
}

int	dup_opt_wrd(t_data *data, t_env *env, char *cmd)
{
	t_env	*trav;

	trav = data->l_env;
	while (ft_strcmp(trav->sec, cmd) && trav->next)
		trav = trav->next;
	if (!ft_strcmp(trav->sec, cmd))
		return (0);
	else
		env->sec = ft_strdup(cmd);
	return (1);
}

int	check_if_equal_or_wrd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
