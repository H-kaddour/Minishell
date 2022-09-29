/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:12:08 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/29 12:06:58 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_alloc(t_data *data, char *dolla, char *ptr)
{
	int	len;
	char	*hold;

	hold = dolla;
	dolla = myown_getenv(data, dolla, 0);
	if (!dolla)
		dolla = hold;
	else
		free(hold);
	len = 0;
	while (dolla[len])
		ptr[data->j++] = dolla[len++];
}

static void	heredoc_dolla_allocate(t_data *data, char *ptr, char *str)
{
	int		len;
	char	*dolla;
	t_env	*trav_env;

	trav_env = data->l_env;
	if (str[data->i] == '$' && ft_acceptable_char(str[data->i + 1]))
	{
		data->i++;
		len = 0;
		while (ft_acceptable_char(str[data->i]))
		{
			data->i++;
			len++;
		}
		dolla = malloc(sizeof(char) * len + 1);
		if (!dolla)
			return ;
		data->i -= len;
		len = 0;
		while (ft_acceptable_char(str[data->i]))
			dolla[len++] = str[data->i++];
		heredoc_alloc(data, dolla, ptr);
	}
}

void	heredoc_dolla_helper(t_data *data, char *str, char *ptr)
{
	int		i;
	char	*tmp;

	if (str[data->i + 1] == '?')
	{
		data->i +=2;
		tmp = ft_itoa(data->chk_dolla);
		i = 0;
		while (tmp[i])
			ptr[data->j++] = tmp[i++];
	}
	if (str[data->i + 1] == '0')
	{
		i = 2;
		while (data->args[0][i])
			ptr[data->j++] = data->args[0][i++];
		data->i += 2;
	}
}

static void	heredoc_dolla(t_data *data, char *ptr, char *str)
{
	heredoc_dolla_helper(data, str, ptr);
	if (str[data->i + 1] >= '1' && str[data->i + 1] <= '9')
		data->i += 2;
	if (str[data->i + 1] == '$')
	{
		while (str[data->i] == '$')
		{
			if (str[data->i + 1] == '$')
				data->i += 2;
			else
				break ;
		}
	}
	if ((str[data->i + 1] >= 'A' && str[data->i + 1] <= 'Z') ||\
			(str[data->i + 1] >= 'a' && str[data->i + 1] <= 'z') || str[data->i + 1] == '_')
		heredoc_dolla_allocate(data, ptr, str);
	if (str[data->i + 1] == '\"' || str[data->i + 1] == '\'')
		return ;
}

static char	*fill_data(t_data *data, char *str)
{
	char	*ptr;

	data->i = 0;
	data->j = 0;
	ptr = malloc(sizeof(char) * 100);
	while (str[data->i])
	{
		if (str[data->i] == '$')
			heredoc_dolla(data, ptr, str);
		ptr[data->j++] = str[data->i++];
	}
	printf("%s\n", ptr);
	return (ptr);
}

void	heredoc_sig(int c)
{
	exit(2);
}

void	heredoc_process(t_data *data, char *det)
{
	char	*heredoc;
	char	*buff;

	buff = ft_strdup("");
	signal(SIGINT, heredoc_sig);
	while (1)
	{
		heredoc = readline("> ");
		if (!heredoc)
			exit(0);
		if (!ft_strcmp(heredoc, det))
			break ;
		if (data->chk_q_hrdoc == 0)
			heredoc = fill_data(data, heredoc);
		buff = ft_strjoin(buff, ft_strjoin(heredoc, "\n"));
	}
	ft_putstr_fd(buff, data->hrdoc_fd[1]);
	close(data->hrdoc_fd[1]);
	exit(0);
}

void  error_pipe_heredoc(t_data *data, char *msg)
{
  data->chk_dolla = 1;
  printf("%s\n", msg);
}

void	heredoc_implement(t_data *data, char *det)
{
	int		status;
	int		pid;

	if (pipe(data->hrdoc_fd))
		error_pipe_heredoc(data, "error in pipe");
	pid = fork();
	if (pid < 0)
		error_execution(data, "error in fork");
	if (pid == 0)
	{
		close(data->hrdoc_fd[0]);
		heredoc_process(data, det);
	}
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (status == 512)
			data->chk_hrdoc_exit = 1;
		close(data->hrdoc_fd[1]);
		return ;
	}
}
