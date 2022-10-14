/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_everywhere_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:57:04 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/12 21:23:29 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	old_pwd_alloc(t_data *data)
{
	t_env	*node;
	t_env	*trav;

	trav = data->l_env;
	node = node_allocate();
	node->sec = ft_strdup("OLDPWD");
	while (trav->next)
		trav = trav->next;
	trav->next = node;
	sort_env(data);
	data->old_pwd_make = 1;
}

void	change_pwd(t_data *data, char *path)
{
	t_env	*pwd;

	pwd = getenv_addr(data, "PWD");
	if (!pwd)
	{
		free_implementation(data, data->old_pwd_value);
		data->old_pwd_value = ft_strdup(data->pwd_of_mysys);
		free_implementation(data, data->pwd_of_mysys);
		data->pwd_of_mysys = ft_strdup(path);
	}
	else
	{
		free_implementation(data, data->old_pwd_value);
		data->old_pwd_value = ft_strdup(pwd->value);
		if (!ft_strcmp(pwd->value, path))
			return ;
		else
		{
			free_implementation(data, pwd->value);
			pwd->value = ft_strdup(path);
			free_implementation(data, data->pwd_of_mysys);
			data->pwd_of_mysys = ft_strdup(path);
		}
	}
}

void	change_oldpwd(t_data *data)
{
	t_env	*old;

	old = getenv_addr(data, "OLDPWD");
	if (old)
	{
		free_implementation(data, old->value);
		old->value = ft_strdup(data->old_pwd_value);
	}
}
