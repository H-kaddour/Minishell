/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:02:51 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/13 10:03:10 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_tab_pipe(t_cmd *trav, int *fd)
{
	trav->tab_pipe[0] = fd[1];
	trav->tab_pipe[1] = fd[0];
}

static int	plug_pipes_in_node(t_data *data)
{
	t_cmd	*trav;
	int		fd[2];

	trav = data->v_cmd;
	while (trav->next)
	{
		if (pipe(fd) < 0)
		{
			error_fork(data);
			return (1);
		}
		trav->tab_pipe = malloc(sizeof(int) * 2);
		if (!trav->tab_pipe)
			error_alloc();
		init_tab_pipe(trav, fd);
		trav->f_out = fd[1];
		trav = trav->next;
		trav->f_in = fd[0];
	}
	trav->tab_pipe = malloc(sizeof(int) * 2);
	if (!trav->tab_pipe)
		error_alloc();
	init_tab_pipe(trav, fd);
	trav = data->v_cmd;
	return (0);
}

static void	plug_redirection_in_node(t_data *data)
{
	t_cmd	*trav;
	//int		hld_in;
	//int		hld_out;

	trav = data->v_cmd;
	while (trav)
	{
		//hld_in = trav->f_in;
		//hld_out = trav->f_out;
		check_redirection(data, trav);
		//if (hld_in > trav->f_in)
		//	close(hld_in);
		//if (hld_out > trav->f_out)
		//	close(hld_out);
		trav = trav->next;
	}
}

static void	child_process_of_pipeline(t_data *data, t_cmd *trav)
{
	if (check_builtin(data, &trav->cmd[0]))
	{
		dup2(trav->f_out, STDOUT_FILENO);
		builtin_cmd(data, trav);
		close(trav->tab_pipe[0]);
		close(trav->tab_pipe[1]);
		exit(0);
	}
	else
	{
		dup2(trav->f_out, STDOUT_FILENO);
		dup2(trav->f_in, STDIN_FILENO);
		close(trav->tab_pipe[0]);
		close(trav->tab_pipe[1]);
		execute_sys_cmd(data, trav);
	}
}

void	print_fds(t_data *data)
{
	t_cmd *cmd;

	cmd = data->v_cmd;
	while (cmd)
	{
		if (cmd->cmd[0])
			printf("cmd = %s	f_in = %d	f_out = %d\n", cmd->cmd[0], cmd->f_in, cmd->f_out);
		else
			printf("f_in = %d	f_out = %d\n", cmd->f_in, cmd->f_out);
		cmd = cmd->next;
	}
}

void	pipeline(t_data *data)
{
	int		pid;
	t_cmd	*trav;
	t_cmd	*p_trav;

	if (plug_pipes_in_node(data))
		pipeline_helper(data);
	plug_redirection_in_node(data);
	//print_fds(data);
	//while (1);
	trav = data->v_cmd;
	p_trav = 0;
	while (trav)
	{
		pid = fork();
		if (pid < 0)
			error_fork(data);
		if (pid == 0)
			child_process_of_pipeline(data, trav);
		if (p_trav)
			close(p_trav->tab_pipe[1]);
		close(trav->tab_pipe[0]);

		if (trav->f_in > 0)
			close(trav->f_in);
		if (trav->f_out > 1)
			close(trav->f_out);

		//if (!trav->cmd[0])
		//	close(p_trav->f_out);

		p_trav = trav;
		trav = trav->next;
	}
	pipeline_parent(data);
}
