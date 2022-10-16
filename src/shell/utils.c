/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:11:04 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/16 11:36:41 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	usage_help_menu(char *option)
{
	if (!ft_strcmp(option, "-h"))
	{
		printf("*************************************************.....******\n");
		printf("                                                 O O  /     \n");
		printf("                                                /<   /      \n");
		printf("                 __   _          ___ __________/_#__=o      \n");
		printf(" ___ ___  __ _  / /  (_)__      /(- /(\\_\\________   \\    \n");
		printf("/_ // _ \\/  ' \\/ _ \\/ / -_)     \\ ) \\ )_      \\o     \\ \n");
		printf("/__/\\___/_/_/_/_.__/_/\\__/      /|\\ /|\\       |'     |    \n");
		printf("       __       ____                          /o   __\\     \n");
		printf("  ___ / /  ___ / / /                         / '     |      \n");
		printf(" (_-</ _ \\/ -_) / /                        /_/\\______|     \n");
		printf("/___/_//_/\\__/_/_/                        (   _(    <       \n");
		printf("                                           \\    \\    \\   \n");
		printf("                                             \\____\\___\\  \n");
		printf("Coded by: hkaddour & akouame                 ____\\_\\___\\ \n");
		printf("                                            |___ |_______|..\n");
		printf("\nUsage\n\trun ./minishell with no args\n");
	}
	else
	{
		printf("minishell: %s: No such argument use -h for help\n", option);
		exit(127);
	}
}

void	process_kill(t_data *data)
{
	printf(MOVE_UP_RIGHRT "\t\texit\n");
	//free_data_die_process(data);
	exit(131);
}

//i don't need it anymore
int	hrdoc_with_no_cmd_to_close_fd(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	t_red	*red;

	i = 0;
	cmd = data->v_cmd;
	while (cmd)
	{
		if (!cmd->cmd[0])
		{
			red = cmd->redirect;
			while (red)
			{
				if (red->typ == I_APEND)
				{
					close(data->hrdoc_fd[0]);
					return (1);
				}
				red = red->next;
			}
		}
		cmd = cmd->next;
	}
	return (0);
}
