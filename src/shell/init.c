/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:15:39 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/13 11:51:27 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	make_myown_env(t_data *data)
{
	data->l_env = node_allocate();
	data->l_env->sec = ft_strdup("PWD");
	data->l_env->value = ft_calloc(1024, sizeof(char));
	if (!data->l_env->value)
		error_alloc();
	getcwd(data->l_env->value, 1024);
	data->pwd_of_mysys = ft_strdup(data->l_env->value);
	data->l_env->next = node_allocate();
	data->l_env->next->sec = ft_strdup("SHLVL");
	data->l_env->next->value = ft_strdup("1");
}

static void	add_pwd_if_not_exist(t_data *data)
{
	t_env	*env;

	env = data->l_env;
	while (env->next)
		env = env->next;
	env->next = node_allocate();
	env = env->next;
	env->sec = ft_strdup("PWD");
	env->value = ft_strdup(data->pwd_of_mysys);
}

static void	check_if_env_exist_and_get_it(t_data *data, char **env)
{
	t_env	*trav;

	if (!env[0])
		make_myown_env(data);
	else
	{
		data->env = env;
		get_env(data);
		trav = getenv_addr(data, "PWD");
		if (!trav)
		{
			data->pwd_of_mysys = ft_calloc(1024, sizeof(char));
			if (!data->pwd_of_mysys)
				error_alloc();
			getcwd(data->pwd_of_mysys, 1024);
			add_pwd_if_not_exist(data);
		}
		sort_env(data);
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
	data->free_ptr = free_add_node();
	check_if_env_exist_and_get_it(data, env);
}
