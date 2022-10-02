/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_everywhere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:53:53 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/02 03:43:46 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	cd_to_home(t_data *data, char **cmd)
{
	char	*home;

	home = myown_getenv(data, "HOME", 0);
	if (!home)
	{
		error_cd(data, "minishell: cd: HOME not set");
		return (1);
	}
	*cmd = ft_strdup(home);
	return (0);
}

static int	join_home_and_path(t_data *data, char **cmd)
{
	char	*home;

	home = myown_getenv(data, "HOME", 0);
	if (!home)
	{
		home = getenv("HOME");
		if (!home)
		{
			error_cd(data, "minishell: cd: HOME not set");
			return (1);
		}
	}
	*cmd = ft_strjoin(home, &cmd[0][1]);
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
	getcwd(path, 1024);
	if (data->old_pwd_make == 0)
		old_pwd_alloc(data);
	change_pwd(data, path);
	change_oldpwd(data);
	data->chk_dolla = 0;
}

void	cd_everywhere_at_once(t_data *data, char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
	{
		if (cd_to_home(data, &cmd))
			return ;
	}
	else if (cmd[0] == '~')
	{
		if (join_home_and_path(data, &cmd))
			return ;
	}
	execute_cmd_cd(data, cmd);
}
