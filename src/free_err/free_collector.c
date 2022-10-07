/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_collector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 04:51:31 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 11:01:17 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_exec_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->env_exec)
	{
		while (data->env_exec[i])
		{
			free(data->env_exec[i]);
			i++;
		}
		free(data->env_exec);
	}
	data->env_exec = 0;
}

static void	free_token(t_data *data)
{
	t_token	*token;

	token = data->t_token;
	while (token)
	{
		if (token->value[0])
			free(token->value);
		if (token)
			free(token);
		if (token->next)
			token = token->next;
		else
			break ;
	}
	data->t_token = 0;
}

void	free_data_running_process(t_data *data)
{
	free(data->line);
	free_exec_env(data);
	if (!data->t_token)
		return ;
	free_token(data);
	if (!data->v_cmd)
		return ;
	free_parsing_cmd(data);
	if (data->prompt)
		free(data->prompt);
}

void	free_data_die_process(t_data *data)
{
	t_env	*env;

	env = data->l_env;
	if (data->pwd_of_mysys)
		free(data->pwd_of_mysys);
	while (env)
	{
		free(env->sec);
		free(env->value);
		free(env);
		env = env->next;
	}
	if (data->prompt)
		free(data->prompt);
}
