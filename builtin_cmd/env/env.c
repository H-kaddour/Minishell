/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:11:41 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/02 04:00:46 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*myown_getenv(t_data *data, char *sec, int *status)
{
	t_env	*env;

	env = data->l_env;
	while (ft_strcmp(env->sec, sec) && env->next)
		env = env->next;
	if (!ft_strcmp(env->sec, sec))
	{
		if (status)
			*(status) = 1;
		return (ft_strdup(env->value));
	}
	else
	{
		if (status)
			*(status) = 0;
		return (0);
	}
}

t_env	*getenv_addr(t_data *data, char *sec)
{
	t_env	*env;

	env = data->l_env;
	while (ft_strcmp(env->sec, sec) && env->next)
		env = env->next;
	if (!ft_strcmp(env->sec, sec))
		return (env);
	else
		return (0);
}

void	env_cmd(t_data *data)
{
	t_env	*trav;
	t_cmd	*cmd;

	trav = data->l_env;
	cmd = data->v_cmd;
	if (cmd->cmd[1] != 0)
	{
		data->chk_dolla = 1;
		printf("env: %s: No such file or directory\n", cmd->cmd[1]);
		return ;
	}
	else
	{
		data->chk_dolla = 0;
		while (trav)
		{
			if (!trav->value)
				trav = trav->next;
			else
				printf("%s=%s\n", trav->sec, trav->value);
			if (!trav)
				break ;
			trav = trav->next;
		}
	}
}
