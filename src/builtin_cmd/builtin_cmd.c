/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:54:38 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/12 12:42:21 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*if_upper_lower_them(t_data *data, char *cmd)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc(sizeof(char) * ft_strlen(cmd) + 1);
	if (!ptr)
		error_malloc();
	while (cmd[i])
	{
		if (cmd[i] >= 'A' && cmd[i] <= 'Z')
			ptr[i] = cmd[i] + 32;
		else
			ptr[i] = cmd[i];
		i++;
	}
	ptr[i] = 0;
	free_implementation(data, ptr);
	return (ptr);
}

static int	cmd_only_exec_lower(t_data *data, char *cmd)
{
	int		i;
	char	**sp;
	char	*b_cmd;

	b_cmd = "cd export unset exit";
	i = 0;
	sp = ft_split(b_cmd, ' ');
	free_sp(data, sp);
	//free_implementation(data, sp);
	//while (sp[i])
	//{
	//	free_implementation(data, sp[i]);
	//	i++;
	//}
	//i = 0;
	while (sp[i])
	{
		if (!ft_strcmp(sp[i], cmd))
		{
			//free_sp(data, sp);
			return (1);
		}
		i++;
	}
	//free_sp(data, sp);
	return (0);
}

static int	check_builtin_helper(t_data *data, char *cmd)
{
	int		i;
	char	**sp;
	char	*b_cmd;

	i = 0;
	b_cmd = "env echo pwd";
	sp = ft_split(b_cmd, ' ');
	free_sp(data, sp);
	//free_implementation(data, sp);
	//while (sp[i])
	//{
	//	free_implementation(data, sp[i]);
	//	i++;
	//}
	//i = 0;
	while (sp[i])
	{
		if (!ft_strcmp(sp[i], cmd))
		{
			//free_sp(data, sp);
			return (1);
		}
		i++;
	}
	//free_sp(data, sp);
	return (0);
}

int	check_builtin(t_data *data, char **cmd)
{
	int		i;
	char	*b_cmd;

	if (cmd_only_exec_lower(data, *cmd))
		return (1);
	i = 0;
	b_cmd = *cmd;
	//free_implementation(data, *cmd);
	while (!(b_cmd[i] >= 'A' && b_cmd[i] <= 'Z') && b_cmd[i])
		i++;
	if (b_cmd[i])
	{
		//free_implementation(data, b_cmd);
		*cmd = if_upper_lower_them(data, *cmd);
		//free_implementation(data, *cmd);
	}
	if (check_builtin_helper(data, *cmd))
		return (1);
	return (0);
}

void	builtin_cmd(t_data *data, t_cmd *node)
{
	if (!ft_strcmp(node->cmd[0], "cd"))
		cd_cmd(data, node);
	else if (!ft_strcmp(node->cmd[0], "echo"))
		echo_cmd(data, node);
	else if (!ft_strcmp(node->cmd[0], "pwd"))
		pwd_cmd(data);
	else if (!ft_strcmp(node->cmd[0], "env"))
		env_cmd(data, node);
	else if (!ft_strcmp(node->cmd[0], "export"))
		export_cmd(data, node);
	else if (!ft_strcmp(node->cmd[0], "unset"))
		unset_cmd(data, node);
	else if (!ft_strcmp(node->cmd[0], "exit"))
		exit_cmd(data, node);
}
