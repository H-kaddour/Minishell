/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_value_len_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:14:23 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 11:09:03 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	count_d_quote_helper(t_data *data)
{
	if (data->beg_line[data->i] == '\"' || data->beg_line[data->i] == '\'')
	{
		if (data->beg_line[data->i] == '\'')
		{
			data->i++;
			data->tok_len++;
		}
		else if (data->beg_line[data->i] == '\"')
			data->i++;
	}
}

static void	count_arg_after_hrdoc_helper(t_data *data, int *c)
{
	int	i;

	i = data->i + 1;
	while (data->beg_line[i])
	{
		if (data->beg_line[i] == '\"' || data->beg_line[i] == '\"')
		{
			if (data->beg_line[i] == '\"')
				*c = '\"';
			else if (data->beg_line[i] == '\'')
				*c = '\'';
			break ;
		}
		i++;
	}
}

void	count_arg_after_hrdoc(t_data *data)
{
	int	c;
	int	i;

	i = data->i + 1;
	count_arg_after_hrdoc_helper(data, &c);
	if (c == '\'' || c == '\"')
		data->chk_q_hrdoc = 1;
	while (data->beg_line[data->i] != ' ' && data->beg_line[data->i] && \
		&data->beg_line[data->i] != &data->n_line[0])
	{
		if (data->beg_line[data->i] == c)
			data->i++;
		else
		{
			data->i++;
			data->tok_len++;
		}
	}
	data->chk_hrdoc = 0;
}
