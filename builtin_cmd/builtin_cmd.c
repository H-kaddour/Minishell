/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:54:38 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/02 03:30:11 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*if_upper_lower_them(char *cmd)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc(sizeof(char) * ft_strlen(cmd) + 1);
	while (cmd[i])
	{
		if (cmd[i] >= 'A' && cmd[i] <= 'Z')
			ptr[i] = cmd[i] + 32;
		else
			ptr[i] = cmd[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

int	cmd_only_exec_lower(char *cmd)
{
	int		i;
	char	**sp;
	char	*b_cmd;

	b_cmd = "cd export unset exit";
	i = 0;
	sp = ft_split(b_cmd, ' ');
	while (sp[i])
	{
		if (!ft_strcmp(sp[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

int	check_builtin(char **cmd)
{
	int		i;
	char	**sp;
	char	*b_cmd;

	if (cmd_only_exec_lower(*cmd))
		return (1);
	i = 0;
	b_cmd = *cmd;
	while (!(b_cmd[i] >= 'A' && b_cmd[i] <= 'Z') && b_cmd[i])
		i++;
	if (b_cmd[i])
		*cmd = if_upper_lower_them(*cmd);
	b_cmd = "env echo pwd";
	sp = ft_split(b_cmd, ' ');
	i = 0;
	while (sp[i])
	{
		if (!ft_strcmp(sp[i], *cmd))
			return (1);
		i++;
	}
	return (0);
}

void	builtin_cmd(t_data *data, char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		cd_cmd(data);
	else if (!ft_strcmp(cmd, "echo"))
		echo_cmd(data);
	else if (!ft_strcmp(cmd, "pwd"))
		pwd_cmd(data);
	else if (!ft_strcmp(cmd, "env"))
		env_cmd(data);
	else if (!ft_strcmp(cmd, "export"))
		export_cmd(data);
	else if (!ft_strcmp(cmd, "unset"))
		unset_cmd(data);
	else if (!ft_strcmp(cmd, "exit"))
		exit_cmd(data);
}
