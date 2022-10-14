/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_value_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:04:36 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/13 14:20:51 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	count_s_quote(t_data *data)
{
	data->i++;
	data->chk_q_hrdoc = 1;
	while (data->beg_line[data->i] != '\'' && data->beg_line[data->i])
	{
		data->i++;
		data->tok_len++;
	}
	if (data->beg_line[data->i] == '\'')
	{
		data->chk_q_hrdoc = 1;
		data->i++;
	}
}

static void	loop_d_quote(t_data *data)
{
	while (data->beg_line[data->i] != ' ' \
			&& data->beg_line[data->i] != '\"' && data->beg_line[data->i] \
			&& &data->beg_line[data->i] != &data->n_line[0])
	{
		data->i++;
		data->tok_len++;
	}
	data->chk_hrdoc = 0;
}

static void	count_d_quote(t_data *data)
{
	data->i++;
	data->chk_q_hrdoc = 1;
	while (data->beg_line[data->i] != '$' && \
			data->beg_line[data->i] != '\"' && data->beg_line[data->i])
	{
		data->i++;
		data->tok_len++;
	}
	while (data->beg_line[data->i] == '$')
	{
		if (data->chk_hrdoc == 1)
			loop_d_quote(data);
		else
		{
			if (!count_dolla_begin(data))
				count_dolla(data);
		}
		while (data->beg_line[data->i] != '$' && \
				data->beg_line[data->i] != '\"' && data->beg_line[data->i])
			data->i++;
	}
	count_d_quote_helper(data);
}

static void	get_len_helper(t_data *data)
{
	if (data->beg_line[data->i] == '\'')
		count_s_quote(data);
	if (data->beg_line[data->i] == '\"')
		count_d_quote(data);
	data->d_q_chk = 0;
	while (data->beg_line[data->i] == '$' \
			&& &data->beg_line[data->i] != &data->n_line[0])
	{
		if (data->chk_hrdoc == 1)
			count_arg_after_hrdoc(data);
		else
		{
			if (!count_dolla_begin(data))
				count_dolla(data);
		}
	}
}

int	get_len(t_data *data)
{
	data->i = 0;
	data->tok_len = 0;
	data->chk_q_hrdoc = 0;
	while (&data->beg_line[data->i] != &data->n_line[0] \
			&& data->beg_line[data->i])
	{
		get_len_helper(data);
		if (&data->beg_line[data->i] == &data->n_line[0])
			break ;
		if (data->beg_line[data->i] != '\"' && \
				data->beg_line[data->i] != '\'' && data->beg_line[data->i])
		{
			data->i++;
			data->tok_len++;
		}
	}
	return (data->tok_len);
}
