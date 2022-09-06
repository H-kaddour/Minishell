/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:12:08 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/06 22:00:03 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static void	heredoc_dolla_allocate(t_data *data, char *ptr, char *str, int *i, int *j)
{
	//int		k;
	int		len;
	char	*dolla;
	t_env	*trav_env;

	trav_env = data->l_env;
	if (str[(*i)] == '$' && ft_acceptable_char(str[(*i) + 1]))
	{
		(*i)++;
		len = 0;
		while (ft_acceptable_char(str[(*i)]))
		{
			(*i)++;
			len++;
		}
		dolla = malloc(sizeof(char) * len + 1);
		if (!dolla)
			return ;
		(*i) -= len;
		len = 0;
		while (ft_acceptable_char(str[(*i)]))
			dolla[len++] = str[(*i)++];
		while (ft_strcmp(dolla, trav_env->value) && trav_env->next != 0)
			trav_env = trav_env->next;
		if (ft_strcmp(dolla, trav_env->value))
		{
			free(dolla);
			dolla = ft_strdup(trav_env->value);
		}
		else
		{
			free(dolla);
			dolla = ft_strdup(trav_env->value);
		}
		len = 0;
		while (dolla[len])
			ptr[(*j)++] = dolla[len++];
	}
}

static void	heredoc_dolla(t_data *data, char *ptr, char *str, int *i, int *j)
{
	int		k;
	char	*tmp;

	if (str[(*i) + 1] == '?')
	{
		(*i) += 2;
		tmp = ft_itoa(data->chk_dolla);
		k = 0;
		while (tmp[k])
			ptr[(*j)++] = tmp[k++];
	}
	if (str[(*i) + 1] == '0')
	{
		//ignore ./ of prgram
		k = 2;
		while (data->args[0][k])
			ptr[(*j)++] = data->args[0][k++];
		(*i) += 2;
	}
	if (str[(*i) + 1] >= '1' && str[(*i) + 1] <= '9')
	{
		(*i) += 2;
	}
	if (str[(*i) + 1] == '$')
	{
		while (str[(*i)] == '$')
		{
			if (str[(*i) + 1] == '$')
				(*i) += 2;
			else
				break ;
		}
	}
	if ((str[(*i) + 1] >= 'A' && str[(*i) + 1] <= 'Z') ||\
			(str[(*i) + 1] >= 'a' && str[(*i) + 1] <= 'z') || str[(*i) + 1] == '_')
	{
		heredoc_dolla_allocate(data, ptr, str, i, j);
	}
	if (str[(*i) + 1] == '\"' || str[(*i) + 1] == '\'')
		return ;
}

static char	*fill_data(t_data *data, char *str)
{
	//if chk_q_hrdoc == 0 so i will expand the dolla if equal 1 i will not expand and "" '' should not ignore
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = malloc(sizeof(char) * 100);
	while (str[i])
	{
		if (str[i] == '$')
			heredoc_dolla(data, ptr, str, &i, &j);
		//maybe here else
		ptr[j++] = str[i++];
	}
	return (ptr);
}

//void  heredoc_sig(int c)
//{
//  if (c == SIGINT)
//	{
//    printf("\n");
//    rl_on_new_line();
//    rl_replace_line("", 0);
//    rl_redisplay();
//  }
//  else if (c == SIGQUIT)
//  {
//    printf("\n");
//    exit(0);
//  }
//}

void	heredoc_implement(t_data *data, char *det)
{
	char	*heredoc;
	char	*buff;
	char	*tmp;
	int		len;

	//buff = malloc(sizeof(char) * 1);
	//buff[0] = 0;
	buff = ft_strdup("");
	//heredoc = readline("> ");
	//if (!heredoc)
	//	return ;
	//while (ft_strncmp(heredoc, det, ft_strlen(det)))
	while (1)
	{
		//signal(SIGINT, heredoc_sig);
		//for the signal just fork and in the child run the heredoc and when u ctrl c exit(0) and in the parent will exit too ignore it
		heredoc = readline("> ");
		if (!heredoc)
			return ;
		if (!ft_strcmp(heredoc, det))
			break ;
		if (data->chk_q_hrdoc == 0)
			heredoc = fill_data(data, heredoc);
		buff = ft_strjoin(buff, ft_strjoin(heredoc, "\n"));
		//fill_data(data, heredoc);
		//and here i should send the data i enter to a file and expand it and all that shiit
	}
	pipe(data->hrdoc_fd);
	ft_putstr_fd(buff, data->hrdoc_fd[1]);
	close(data->hrdoc_fd[1]);
	tmp = malloc(ft_strlen(buff) + 1);
	len = read(data->hrdoc_fd[0], tmp, ft_strlen(buff));
	len++;
	tmp[len] = 0;
	printf("%s", tmp);

}
//ls << $PW' just i didn't add DOLLA type in lexer pt1
