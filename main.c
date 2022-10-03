/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:34:24 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/02 17:24:02 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_c(int c)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	new_prompt(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	prompt_changer(t_data *data)
{
	t_env	*pwd;
	t_env	*home;
	char	*path_h;
	char	*path_pw;
	int		len;
	int		i;
	char	*clr1;
	char	*clr2 = " \e[0m\e[34m \e[0m";
	char	*tmp;

	if (data->prompt)
		free(data->prompt);
	if (data->chk_dolla == 0)
		clr1 = "\e[40m \e[97m \e[44m\e[30m\e[44m \e[30m";
	else
		clr1 = "\e[103m \e[91m \e[40m\e[93m \e[97m \e[44m\e[30m\e[44m \e[30m";
	//pwd = data->l_env;
	pwd = getenv_addr(data, "PWD");
	if (pwd)
		path_pw = pwd->value;
	else
		path_pw = data->pwd_of_mysys;
	//path_h = myown_getenv(data, "HOME", 0);
	home = getenv_addr(data, "HOME");
	if (home)
		path_h = home->value;
	else
		path_h = getenv("HOME");
	if (!path_h)
	{
		tmp = ft_strjoin(path_pw, clr2);
		data->prompt = ft_strjoin(clr1, tmp);
		free(tmp);
		return ;
	}
	if (!ft_strncmp(path_pw, path_h, ft_strlen(path_h)))
	{
		if (ft_strlen(path_pw) > ft_strlen(path_h))
		{
			len = ft_strlen(path_h);
			data->prompt = malloc(sizeof(char) * len + 3);
			i = 0;
			data->prompt[i++] = '~';
			while (path_pw[len])
				data->prompt[i++] = path_pw[len++];
			data->prompt[i] = 0;
			tmp = ft_strjoin(data->prompt, clr2);
			free(data->prompt);
			data->prompt = ft_strjoin(clr1, tmp);
			free(tmp);
		}
		else if (ft_strlen(path_pw) == ft_strlen(path_h))
		{
			tmp = ft_strjoin("~", clr2);
			data->prompt = ft_strjoin(clr1, tmp);
			free(tmp);
		}
	}
	else
	{
		tmp = ft_strjoin(path_pw, clr2);
		data->prompt = ft_strjoin(clr1, tmp);
		free(tmp);
	}
}

void	make_myown_env(t_data *data)
{
	data->l_env = node_allocate();
	data->l_env->sec = "PWD";
	data->l_env->value = malloc(1024);
	getcwd(data->l_env->value, 1024);
	data->pwd_of_mysys = data->l_env->value;
	data->l_env->next = node_allocate();
	data->l_env->next->sec = "SHLVL";
	data->l_env->next->value = "1";
}

void	add_pwd(t_data *data)
{
	t_env	*env;

	env = data->l_env;
	while (env->next)
		env = env->next;
	env->next = node_allocate();
	env = env->next;
	env->sec = "PWD";
	env->value = data->pwd_of_mysys;
}

void	init_shell_elem(t_data *data, char **av, char **env)
{
	data->args = av;
	data->old_pwd_make = 0;
	data->chk_redct_exist = 0;
		data->chk_dolla = 0;
	data->old_pwd_value = ft_strdup("");
	data->prompt = 0;
	if (!env[0])
		make_myown_env(data);
	else
	{
		data->env = env;
		get_env(data);
		data->pwd_of_mysys = myown_getenv(data, "PWD", &data->status_of_oldpwd);
		if (!data->pwd_of_mysys)
		{
			data->pwd_of_mysys = malloc(sizeof(char) * 1024);
			getcwd(data->pwd_of_mysys, 1024);
			add_pwd(data);
		}
	}
}

void	add_shell_history(t_data *data)
{
	int	i;

	i = 0;
	if (data->line[0])
	{
		while (data->line[i] == ' ' || (data->line[i] >= 9 && data->line[i] <= 13))
			i++;
		if (data->line[i])
			add_history(data->line);
	}
}

void	free_all(t_data *data)
{
	t_token	*token;
	t_cmd		*parse;
	t_red		*red;
	int			i;

	//always check if the address exist and then free in case tokenizer show error in first of implementing
	token = data->t_token;
	parse = data->v_cmd;
	while (token)
	{
		free(token->value);
		free(token);
		token = token->next;
	}
	while (parse)
	{
		i = 0;
		while (parse->cmd[i])
		{
			free(parse->cmd[i]);
			i++;
		}
		free(parse->cmd);
		if (parse->redirect)
		{
			red = parse->redirect;
			while (red)
			{
				if (red->file)
					free(red->file);
				if (red->determiner)
					free(red->determiner);
				free(red);
				red = red->next;
			}
		}
		free(parse);
		parse = parse->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int	i = 0;

	if (ac == 1)
	{
		init_shell_elem(&data, av, envp);
		while (1)
		{
			rl_catch_signals = 0;
			signal(SIGINT, sig_c);
			signal(SIGQUIT, SIG_IGN);
			prompt_changer(&data);
			data.line = readline(data.prompt);
			//data.line = readline("cool> ");
			if (!data.line)
			{
				printf(MOVE_UP_RIGHRT "\t\texit\n");
				exit(131);
			}
			if (data.line[0] == 0)
				new_prompt();
			else
			{
				tokenizer(&data);
				if (!data.error_lexer)
					execution(&data);
			}
			add_shell_history(&data);
			free(data.line);
			free_all(&data);
		}
		//and here program end should free all shiit
	}
	else
		return (0);
	return (0);
}
