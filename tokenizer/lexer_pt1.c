/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pt1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:15:30 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/28 10:26:40 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_lexer_helper(int s_c, int d, int s, int typ)
{
	if (s_c >= 2 && typ == WRD)
	{
		printf("minishell: syntax error near unexpected token ';;'\n");
		return (1);
	}
	if (d % 2 == 0 && s % 2 == 0)
		return (0);
	printf("minishell: unclosed quotes\n");
	return (1);
}

static int	quote_lexer(t_data *data, int q1, int q2, int typ)
{
	int	i;
	int	s_quote;
	int	d_quote;
	int	semi_colum;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	semi_colum = 0;
	while (&data->beg_line[i] != &data->n_line[0])
	{
		if (data->beg_line[i] == ';')
			semi_colum++;
		if (data->beg_line[i] == q1 && s_quote % 2 == 0)
			d_quote++;
		else if (data->beg_line[i] == q2 && d_quote % 2 == 0)
			s_quote++;
		i++;
	}
	if (quote_lexer_helper(semi_colum, d_quote, s_quote, typ))
		return (1);
	return (0);
}

static int	pipe_lexer(t_data *data)
{
	if (data->beg_line[0] == '|')
	{
		if (data->beg_line[1] == '|')
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			return (1);
		}
	}
	return (0);
}

static int	redirection_lexer(t_data *data, int c)
{
	if (data->beg_line[2] == c)
	{
		if (c == '>')
			printf("minishell: syntax error near unexpected token '>>'\n");
		if (c == '<')
			printf("minishell: syntax error near unexpected token '<<'\n");
		return (1);
	}
	return (0);
}

int	lexer_redirect_helper(t_data *data, int typ)
{
	if (typ == O_APEND || typ == I_APEND)
	{
		if (typ == O_APEND)
		{
			if (redirection_lexer(data, '>'))
				return (1);
		}
		if (typ == I_APEND)
		{
			if (redirection_lexer(data, '<'))
				return (1);
		}
	}
	return (0);
}

int	lexer_pt1(t_data *data, t_types typ)
{
	if (typ == PIPE)
	{
		if (pipe_lexer(data))
			return (1);
	}
	if (typ == D_QUOT || typ == S_QUOT || typ == WRD || typ == DOLLA)
	{
		if (typ == S_QUOT || typ == WRD || typ == DOLLA)
		{
			if (quote_lexer(data, '\'', '\"', typ))
				return (1);
		}
		if (typ == D_QUOT)
		{
			if (quote_lexer(data, '\"', '\'', typ))
				return (1);
		}
	}
	if (lexer_redirect_helper(data, typ) == 1)
		return (1);
	return (0);
}
