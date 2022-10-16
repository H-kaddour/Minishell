/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:46:07 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/16 11:51:26 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	add_s_quote(t_data *data)
{
	data->i++;
	data->chk_q_hrdoc = 1;
	while (data->beg_line[data->i] != '\'' && data->beg_line[data->i])
		data->node->value[data->j++] = data->beg_line[data->i++];
	if (data->beg_line[data->i] == '\'')
	{
		data->chk_q_hrdoc = 1;
		data->i++;
	}
}

static void	add_d_quote(t_data *data)
{
	data->i++;
	data->chk_q_hrdoc = 1;
	while (data->beg_line[data->i] != '$' && \
			data->beg_line[data->i] != '\"' && data->beg_line[data->i])
		data->node->value[data->j++] = data->beg_line[data->i++];
	while (data->beg_line[data->i] == '$')
	{
		if (data->chk_hrdoc == 1)
		{
			while (data->beg_line[data->i] != ' ' && \
					data->beg_line[data->i] != '\"' && data->beg_line[data->i] \
					&& &data->beg_line[data->i] != &data->n_line[0])
				data->node->value[data->j++] = data->beg_line[data->i++];
			data->chk_hrdoc = 0;
		}
		else
		{
			if (!add_dolla_begin(data))
				add_dolla(data);
		}
		while (data->beg_line[data->i] != '$' && \
				data->beg_line[data->i] != '\"' && data->beg_line[data->i])
			data->node->value[data->j++] = data->beg_line[data->i++];
	}
	add_d_quote_helper(data);
}

static void	add_node_helper(t_data *data)
{
	if (data->beg_line[data->i] == '\'')
		add_s_quote(data);
	if (data->beg_line[data->i] == '\"')
		add_d_quote(data);
	data->d_q_chk = 0;
	while (data->beg_line[data->i] == '$' \
			&& &data->beg_line[data->i] != &data->n_line[0])
	{
		if (data->chk_hrdoc == 1)
			arg_after_hrdoc(data);
		else
		{
			if (!add_dolla_begin(data))
				add_dolla(data);
		}
	}
}

void	loop_for_the_arg(t_data *data)
{
	while (&data->beg_line[data->i] != &data->n_line[0] \
			&& data->beg_line[data->i])
	{
		add_node_helper(data);
		if (&data->beg_line[data->i] == &data->n_line[0])
			break ;
		if (data->beg_line[data->i] != '\"' && \
				data->beg_line[data->i] != '\'' && data->beg_line[data->i])
			data->node->value[data->j++] = data->beg_line[data->i++];
	}
}

int	add_node(t_data *data, t_types typ)
{
	t_env	*trav_env;

	trav_env = data->l_env;
	if (lexer_pt1(data, typ))
		return (1);
	data->node = allocation(data, 1, sizeof(t_token), 1);
	if (data->check == 1)
		data->t_token = data->node;
	data->node->type = typ;
	data->node->value = allocation(data, get_len(data) + 1, sizeof(char), 1);
	data->i = 0;
	data->j = 0;
	data->chk_q_hrdoc = 0;
	loop_for_the_arg(data);
	data->beg_line = &data->beg_line[data->i];
	//data->node->value[data->j] = 0;
	//data->node->next = 0;
	node_attach(data);
	return (0);
}
