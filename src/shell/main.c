/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:34:24 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/09 15:09:41 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	running_process_helper(t_data *data)
{
	if (data->v_cmd)
		hrdoc_with_no_cmd_to_close_fd(data);
	if (data->beg_line)
		add_history(data->line);
	free_data_running_process(data);
}

//void	close_nodes_fds(t_data *data)
//{
//	t_cmd	*cmd;
//
//	cmd = data->v_cmd;
//	while (cmd)
//	{
//		if (cmd)
//		close
//		cmd = cmd->next;
//	}
//}

void	running_process(t_data *data)
{
	t_cmd	*cmd;

	while (1)
	{
		rl_catch_signals = 0;
		signal(SIGINT, sig_c);
		signal(SIGQUIT, SIG_IGN);
		prompt_changer(data);
		data->line = readline(data->prompt);
		if (!data->line)
			process_kill(data);
		tokenizer(data);
		//cmd = data->v_cmd;
		//while (cmd)
		//{
		//	printf("%s\n", cmd->cmd[0]);
		//	printf("%d\n", cmd->hrdoc_fd);
		//	cmd = cmd->next;
		//}
		//printf("hrdc = %d\n", data->hrdoc_fd[1]);
		if (!data->beg_line)
		{
			data->chk_dolla = 0;
			free(data->line);
			continue ;
		}
		if (!data->error_lexer)
		{
			env_double_ptr(data);
			execution(data);
		}
		//running_process_helper(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac == 1)
	{
		init_shell_elem(&data, av, envp);
		running_process(&data);
	}
	else if (ac == 2)
		usage_help_menu(av[1]);
	else
	{
		printf("minishell: %s: No such file or directory\n", av[1]);
		exit(127);
	}
	return (0);
}
