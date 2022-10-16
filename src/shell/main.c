/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:34:24 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/16 18:32:22 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*allocation(t_data *data, size_t count, size_t size, int chk)
{
	void		*ptr;

	ptr = ft_calloc(count, size);
	if (chk)
		add_node_p_running(data, ptr);
	else
		add_node_p_die(data, ptr);
	return (ptr);
}

char	*add_dup(t_data *data, char *s, int chk)
{
	char	*ptr;

	ptr = ft_strdup(s);
	if (chk)
		add_node_p_running(data, ptr);
	else
		add_node_p_die(data, ptr);
	return (ptr);
}

char	*add_join(t_data *data, char *s, char *s1, int chk)
{
	char	*ptr;

	ptr = ft_strjoin(s, s1);
	if (chk)
		add_node_p_running(data, ptr);
	else
		add_node_p_die(data, ptr);
	return (ptr);
}

void	running_process_helper(t_data *data)
{
	if (data->beg_line)
		add_history(data->line);
	//free_data_running_process(data);
}

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
		{
			//while (1);
			process_kill(data);
		}
		tokenizer(data);
		if (!data->beg_line)
		{
			//here don't free the line free all node of running process
			//free(data->line);
			continue ;
		}
		if (!data->error_lexer)
		{
			env_double_ptr(data);
			execution(data);
		}
		running_process_helper(data);
	}
	//while (1);
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
