/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_swaping_oldpwd_pwd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:39:52 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/02 03:57:04 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	execute_cd_swap_init(t_data *data, t_env **pwd, t_env **old)
{
	*pwd = getenv_addr(data, "PWD");
	*old = getenv_addr(data, "OLDPWD");
}

static void	execute_cd_swap_old_pwd(t_data *data)
{
	t_env	*pwd;
	t_env	*old;
	char	*val;

	execute_cd_swap_init(data, &pwd, &old);
	val = old->value;
	if (pwd)
	{
		old->value = pwd->value;
		pwd->value = val;
		data->pwd_of_mysys = ft_strdup(val);
	}
	else
	{
		old->value = data->pwd_of_mysys;
		data->pwd_of_mysys = val;
	}
	if (chdir(val) != 0)
	{
		data->chk_dolla = 1;
		printf("minishell: cd: %s: No such file or directory\n", pwd->value);
		return ;
	}
	data->chk_dolla = 0;
}

static int	check_old_pwd(t_data *data)
{
	t_env	*old;

	old = data->l_env;
	old = getenv_addr(data, "OLDPWD");
	if (old)
		return (0);
	return (1);
}

void	cd_between_pwd_and_oldpwd(t_data *data, char *cmd)
{
	int	i;

	i = 0;
	if (cmd[1] != 0)
	{
		error_cd(data, "minishell: cd: -: invalid option");
		return ;
	}
	else
	{
		if (check_old_pwd(data))
		{
			error_cd(data, "minishell: cd: OLDPWD not set");
			return ;
		}
		else
		{
			execute_cd_swap_old_pwd(data);
			pwd_cmd(data);
		}
	}
}
