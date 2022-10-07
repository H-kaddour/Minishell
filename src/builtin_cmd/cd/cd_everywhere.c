/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_everywhere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:53:53 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 21:37:11 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	cd_to_home(t_data *data, char **cmd)
{
	t_env	*home;

	home = getenv_addr(data, "HOME");
	if (!home)
	{
		error_cd(data, "minishell: cd: HOME not set");
		return (1);
	}
	*cmd = ft_strdup(home->value);
	return (0);
}

static int	join_home_and_path(t_data *data, char **cmd)
{
	t_env	*e_home;
	char	*home;

	e_home = getenv_addr(data, "HOME");
	if (!e_home)
	{
		home = getenv("HOME");
		if (!home)
		{
			error_cd(data, "minishell: cd: HOME not set");
			return (1);
		}
		*cmd = ft_strjoin(home, &cmd[0][1]);
		return (0);
	}
	*cmd = ft_strjoin(e_home->value, &cmd[0][1]);
	return (0);
}

static void	execute_cmd_cd(t_data *data, char *cmd)
{
	char	*path;

	if (chdir(cmd) != 0)
	{
		data->chk_dolla = 1;
		printf("minishell: cd: %s: No such file or directory\n", cmd);
		return ;
	}
	path = malloc(sizeof(char) * 1024);
	if (!path)
		error_malloc();
	getcwd(path, 1024);
	if (access(path, F_OK) != 0)
		printf("cd: error retrieving current directory\n");
	if (data->old_pwd_make == 0)
		old_pwd_alloc(data);
	change_pwd(data, path);
	change_oldpwd(data);
	free(path);
	data->chk_dolla = 0;
}

void	cd_everywhere_at_once(t_data *data, char *cmd)
{
	int	i;
	int	chk;

	i = 0;
	chk = 0;
	if (!cmd)
	{
		if (cd_to_home(data, &cmd))
			return ;
		chk = 1;
	}
	else if (cmd[0] == '~')
	{
		if (join_home_and_path(data, &cmd))
			return ;
		chk = 1;
	}
	execute_cmd_cd(data, cmd);
	if (chk)
		free(cmd);
}
//here a leak
//ls
//cd
//cd
//cd ..
//cd ~
//cd ..
//cd ..
//cd ..
//cd 
//clear
