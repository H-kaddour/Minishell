/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:46:07 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/27 18:44:26 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_s_quote(t_data *data)
{
	data->i++;
	while (data->beg_line[data->i] != '\'' && data->beg_line[data->i])
		data->node->value[data->j++] = data->beg_line[data->i++];
	if (data->beg_line[data->i] == '\'')
		data->i++;
}

static void	add_d_quote(t_data *data)
{
	data->i++;
	while (data->beg_line[data->i] != '$' && \
			data->beg_line[data->i] != '\"' && data->beg_line[data->i])
		data->node->value[data->j++] = data->beg_line[data->i++];
	while (data->beg_line[data->i] == '$')
	{
		if (data->chk_hrdoc == 1)
		{
			while (data->beg_line[data->i] != ' ' && data->beg_line[data->i] != '\"' \
					&& data->beg_line[data->i] && &data->beg_line[data->i] != &data->n_line[0])
				data->node->value[data->j++] = data->beg_line[data->i++];
			data->chk_hrdoc = 0;
		}
		else
		{
			add_dolla_begin(data);
			add_dolla(data);
		}
		while (data->beg_line[data->i] != '$' && \
				data->beg_line[data->i] != '\"' && data->beg_line[data->i])
			data->node->value[data->j++] = data->beg_line[data->i++];
	}
	if (data->beg_line[data->i] == '\"' || data->beg_line[data->i] == '\'')
	{
		if (data->beg_line[data->i] == '\'')
			data->node->value[data->j++] = data->beg_line[data->i++];
		else if (data->beg_line[data->i] == '\"')
			data->i++;
	}
}

static void	add_node_helper(t_data *data, int check)
{
	if (check == 0)
	{
		if (data->beg_line[data->i] == '\'')
			add_s_quote(data);
		if (data->beg_line[data->i] == '\"')
			add_d_quote(data);
		while (data->beg_line[data->i] == '$' \
				&& &data->beg_line[data->i] != &data->n_line[0])
		{
			if (data->chk_hrdoc == 1)
			{
			while (data->beg_line[data->i] != ' ' && data->beg_line[data->i] &&\
					&data->beg_line[data->i] != &data->n_line[0])
					data->node->value[data->j++] = data->beg_line[data->i++];
				data->chk_hrdoc = 0;
			}
			else
			{
				add_dolla_begin(data);
				add_dolla(data);
			}
		}
	}
	if (check == 1)
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
}

int	add_node(t_data *data, t_types typ)
{
	t_env	*trav_env;

	data->i = 0;
	data->j = 0;
	trav_env = data->l_env;
	if (lexer(data, typ))
		return (1);
	data->node = (t_token *) malloc(sizeof(t_token));
	if (data->check == 1)
		data->t_token = data->node;
	data->node->type = typ;
	//i gotta count the lenght for this node
	data->node->value = malloc(sizeof(char) * 100);
	while (&data->beg_line[data->i] != &data->n_line[0] \
			&& data->beg_line[data->i])
	{
		add_node_helper(data, 0);
		if (&data->beg_line[data->i] == &data->n_line[0])
			break ;
		if (data->beg_line[data->i] != '\"' && \
				data->beg_line[data->i] != '\'' && data->beg_line[data->i])
			data->node->value[data->j++] = data->beg_line[data->i++];
	}
	data->beg_line = &data->beg_line[data->i];
	data->node->value[data->j] = 0;
	data->node->next = NULL;
	add_node_helper(data, 1);
	return (0);
}
