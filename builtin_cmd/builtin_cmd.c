/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:54:38 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/05 21:17:56 by hkaddour         ###   ########.fr       */
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

void	free_sp(char **sp)
{
	int	i;

	i = 0;
	while (sp[i])
	{
		free(sp[i]);
		i++;
	}
	free(sp);
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
		{
			free_sp(sp);
			return (1);
		}
		i++;
	}
	free_sp(sp);
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
	{
		*cmd = if_upper_lower_them(*cmd);
		free(b_cmd);
	}
	b_cmd = "env echo pwd";
	sp = ft_split(b_cmd, ' ');
	i = 0;
	while (sp[i])
	{
		if (!ft_strcmp(sp[i], *cmd))
		{
			free_sp(sp);
			return (1);
		}
		i++;
	}
	free_sp(sp);
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
