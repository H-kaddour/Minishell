/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_token_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 07:10:00 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/06 11:44:13 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

static void	arg_after_hrdoc_helper(t_data *data, int *c)
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

void	arg_after_hrdoc(t_data *data)
{
	int	c;
	int	i;

	i = data->i + 1;
	arg_after_hrdoc_helper(data, &c);
	if (c == '\'' || c == '\"')
		data->chk_q_hrdoc = 1;
	while (data->beg_line[data->i] != ' ' && data->beg_line[data->i] &&\
		&data->beg_line[data->i] != &data->n_line[0])
	{
		if (data->beg_line[data->i] == c)
			data->i++;
		else
			data->node->value[data->j++] = data->beg_line[data->i++];
	}
	data->chk_hrdoc = 0;
}

void	node_attach(t_data *data)
{
	if (data->check == 0)
	{
		data->trav = data->t_token;
		while (data->trav->next)
			data->trav = data->trav->next;
		data->trav->next = data->node;
	}
	if (data->check == 1)
		data->check--;
}

void	add_d_quote_helper(t_data *data)
{
	if (data->beg_line[data->i] == '\"' || data->beg_line[data->i] == '\'')
	{
		if (data->beg_line[data->i] == '\'')
			data->node->value[data->j++] = data->beg_line[data->i++];
		else if (data->beg_line[data->i] == '\"')
			data->i++;
	}
}
