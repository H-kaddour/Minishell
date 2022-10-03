/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_of_node_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 05:36:06 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/02 12:05:36 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		{
			while (data->beg_line[data->i] != ' ' && data->beg_line[data->i] != '\"' \
					&& data->beg_line[data->i] && &data->beg_line[data->i] != &data->n_line[0])
			{
				data->i++;
				data->tok_len++;
			}
			data->chk_hrdoc = 0;
		}
		else
		{
			if (!count_dolla_begin(data))
				count_dolla(data);
		}
		while (data->beg_line[data->i] != '$' && \
				data->beg_line[data->i] != '\"' && data->beg_line[data->i])
			data->node->value[data->j++] = data->beg_line[data->i++];
	}
	count_d_quote_helper(data);
}

void	count_arg_after_hrdoc_helper(t_data *data, int *c)
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
	while (data->beg_line[data->i] != ' ' && data->beg_line[data->i] &&\
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
