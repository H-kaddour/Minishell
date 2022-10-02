/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_one_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 04:54:30 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/02 05:27:10 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_file(t_data *data, t_cmd *cmd)
{
	char	*exec;

	if (find_slash(*cmd->cmd))
	{
		exec = *cmd->cmd;
		if (access(exec, F_OK) == 0)
		{
			if (access(exec, X_OK) == 0)
				execve(exec, cmd->cmd, env_double_ptr(data));
			else
			{
				printf("minishell: %s: Permission denied\n", exec);
				exit(126);
			}
		}
		printf("minishell: %s: command not found\n", cmd->cmd[0]);
		exit(127);
	}
}

static void	exec_cmd_path(t_data *data, t_cmd *cmd, char **sp)
{
	int		i;
	char	*path;

	i = 0;
	while (sp[i])
	{
		path = ft_strjoin(ft_strjoin(sp[i], "/"), cmd->cmd[0]);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				execve(path, cmd->cmd, env_double_ptr(data));
			}
			else
			{
				printf("minishell: %s: Permission denied\n", path);
				exit(126);
			}
		}
		free(path);
		i++;
	}
	printf("minishell: %s: command not found\n", cmd->cmd[0]);
	exit(127);
}

void	execute_sys_cmd(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**sp;
	char	*env;

	i = 0;
	exec_file(data, cmd);
	env = myown_getenv(data, "PATH", 0);
	if (!env)
	{
		data->chk_dolla = 1;
		printf("TERM environment variable not set.\n");
	}
	sp = ft_split(env, ':');
	exec_cmd_path(data, cmd, sp);
}

static void	child_process_run_one_cmd(t_data *data)
{
	if (check_builtin(&data->v_cmd->cmd[0]))
		exit(0);
	if (data->chk_redct_exist == 1)
	{
		dup2(data->v_cmd->f_in, STDIN_FILENO);
		dup2(data->v_cmd->f_out, STDOUT_FILENO);
	}
	execute_sys_cmd(data, data->v_cmd);
}

void	run_one_cmd(t_data *data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		error_execution(data, "minishell: fork: error\n");
	if (pid == 0)
	{
		if (data->v_cmd->cmd[0])
			child_process_run_one_cmd(data);
	}
	if (pid >= 1)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		exit_status(&data->chk_dolla, status);
		if (data->v_cmd->cmd[0])
		{
			if (check_builtin(&data->v_cmd->cmd[0]))
				builtin_cmd(data, data->v_cmd->cmd[0]);
		}
		return ;
	}
}
