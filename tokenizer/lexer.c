/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:15:30 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/27 18:57:11 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	s_quote_lexer(t_data *data)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (&data->beg_line[i] != &data->n_line[0])
	{
		if (data->beg_line[i] == '\'' && d_quote % 2 == 0)
		{
			//i++;
			s_quote++;
		}
		else if (data->beg_line[i] == '\"')
		{
			//i++;
			d_quote++;
		}
		i++;
	}
	if (s_quote % 2 == 0)
		return (0);
	return (1);
}

int	pipe_lexer(t_data *data)
{
	if (data->beg_line[0] == '|')
	{
		if (data->beg_line[1] != 0)
			return (1);
	}
	return (0);
	//int	i;

	//i = 0;
	//while (&data->beg_line[i] != &data->n_line[0])
	//{
	//	if (data->beg_line[i] == '|')

	//}
}

int	lexer(t_data *data, t_types typ)
{
	if (typ == PIPE)
	{
		if (pipe_lexer(data))
			return (1);
	}
	if (typ == S_QUOT || typ == WRD)
	{
		if (s_quote_lexer(data))
			return (1);
	}
	if (typ == D_QUOT)
	{
		if (!pipe_lexer(data))
			return (1);
	}
	if (typ == O_APEND)
	{
		if (!pipe_lexer(data))
			return (1);
	}
	if (typ == I_APEND)
	{
		if (!pipe_lexer(data))
			return (1);
	}
	return (0);
}
