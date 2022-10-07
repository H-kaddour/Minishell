/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:02:51 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 14:35:53 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_tab_pipe(t_cmd *trav, int *fd)
{
	trav->tab_pipe[0] = fd[1];
	trav->tab_pipe[1] = fd[0];
}

//static void	plug_pipes_in_node(t_data *data)
static int	plug_pipes_in_node(t_data *data)
{
	t_cmd	*trav;
	int		fd[2];

	trav = data->v_cmd;
	while (trav->next)
	{
		if (pipe(fd))
		{
			ft_putstr_fd("error in fork no resources\n", 2);
			return (1);
		}
			//error_pipe(data, "minishell: pipe: error in pipe");
		trav->tab_pipe = malloc(sizeof(int) * 2);
		if (!trav->tab_pipe)
			error_malloc();
		init_tab_pipe(trav, fd);
		trav->f_out = fd[1];
		trav = trav->next;
		trav->f_in = fd[0];
	}
	trav->tab_pipe = malloc(sizeof(int) * 2);
	if (!trav->tab_pipe)
		error_malloc();
	init_tab_pipe(trav, fd);
	trav = data->v_cmd;
	return (0);
}

static void	plug_redirection_in_node(t_data *data)
{
	t_cmd	*trav;

	trav = data->v_cmd;
	while (trav)
	{
		check_redirection(data, trav);
		trav = trav->next;
	}
}

static void	child_process_of_pipeline(t_data *data, t_cmd *trav)
{
	if (check_builtin(&trav->cmd[0]))
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

void	error_close_pipes(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->v_cmd;
	while (cmd)
	{
		if (cmd->tab_pipe)
		{
			close(cmd->tab_pipe[0]);
			close(cmd->tab_pipe[1]);
		}
		else
			break ;
		cmd = cmd->next;
	}
}

void	print(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->v_cmd;
	while (cmd)
	{
		printf("in= %d   --   out=%d\n", cmd->f_in, cmd->f_out);
		cmd = cmd->next;
	}
}


//void	pipeline(t_data *data)
int	pipeline(t_data *data)
{
	int		pid;
	//int		status;
	t_cmd	*trav;
	t_cmd	*p_trav;

	if (plug_pipes_in_node(data))
	{
		ft_putstr_fd("error in fork and pipe\n", 2);
		error_close_pipes(data);
		return (-3);
	}
	plug_redirection_in_node(data);
	//print(data);
	//while (1);
	trav = data->v_cmd;
	p_trav = 0;
	while (trav)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("error in fork no resources\n", 2);
			return (-3);
		}
			//error_fork(data, "minishell: fork: Resource temporarily \
			//		unavailable");
		if (pid == 0)
			child_process_of_pipeline(data, trav);
		//if (pid > 0)
		//{
		//	signal(SIGINT, SIG_IGN);
		//	waitpid(pid, &status, 0);
		//	pipeline_parent_helper(data, status, p_trav, trav);
			if (p_trav)
				close(p_trav->tab_pipe[1]);
			close(trav->tab_pipe[0]);
			p_trav = trav;
			trav = trav->next;
		//}
		//p_trav = trav;
		//trav = trav->next;
	}
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		if (waitpid(-1, 0, 0) == -1)
		{
			//if (p_trav)
			//	close(p_trav->tab_pipe[1]);
			//close(trav->tab_pipe[0]);
			break ;
		}
	}
	return (0);
}
