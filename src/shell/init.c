/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:15:39 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 15:44:34 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	make_myown_env(t_data *data)
{
	data->l_env = node_allocate();
	data->l_env->sec = "PWD";
	data->l_env->value = malloc(sizeof(char) * 1024);
	if (!data->l_env->value)
		error_malloc();
	getcwd(data->l_env->value, 1024);
	data->pwd_of_mysys = data->l_env->value;
	data->l_env->next = node_allocate();
	data->l_env->next->sec = "SHLVL";
	data->l_env->next->value = "1";
}

static void	add_pwd_if_not_exist(t_data *data)
{
	t_env	*env;

	env = data->l_env;
	while (env->next)
		env = env->next;
	env->next = node_allocate();
	env = env->next;
	env->sec = "PWD";
	env->value = data->pwd_of_mysys;
}

static void	check_if_env_exist_and_get_it(t_data *data, char **env)
{
	//make_myown_env(data);
	if (!env[0])
		make_myown_env(data);
	else
	{
		data->env = env;
		get_env(data);
		data->pwd_of_mysys = myown_getenv(data, "PWD", &data->status_of_oldpwd);
		if (!data->pwd_of_mysys)
		{
			data->pwd_of_mysys = malloc(sizeof(char) * 1024);
			if (!data->pwd_of_mysys)
				error_malloc();
			getcwd(data->pwd_of_mysys, 1024);
			add_pwd_if_not_exist(data);
		}
	}
}

void	init_shell_elem(t_data *data, char **av, char **env)
{
	data->args = av;
	data->old_pwd_make = 0;
	data->chk_redct_exist = 0;
	data->chk_dolla = 0;
	data->old_pwd_value = ft_strdup("");
	data->pwd_of_mysys = 0;
	data->prompt = 0;
	data->env_exec = 0;
	data->v_cmd = 0;
	data->t_token = 0;
	data->env_exec = 0;
	check_if_env_exist_and_get_it(data, env);
}
