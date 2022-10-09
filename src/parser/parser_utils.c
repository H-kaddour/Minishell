/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:12:08 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/09 10:45:06 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_red_node(t_red *node)
{
	node->typ = 0;
	node->file = 0;
	node->determiner = 0;
	node->next = 0;
}

static void	init_cmd_node(t_cmd *node)
{
	node->cmd = 0;
	node->f_in = 0;
	node->f_out = 1;
	node->redirect = 0;
	node->tab_pipe = 0;
	node->hrdoc_fd = 0;
	node->next = 0;
}

void	allocate_red_node(t_data *data, int red_len)
{
	t_red	*head;
	t_red	*node;
	int		i;

	i = 1;
	if (red_len != 0)
	{
		head = malloc(sizeof(t_red));
		if (!head)
			error_malloc();
		init_red_node(head);
		data->trav_cmd->redirect = head;
	}
	while (i < red_len)
	{
		node = malloc(sizeof(t_red));
		if (!node)
			error_malloc();
		init_red_node(node);
		head->next = node;
		head = node;
		i++;
	}
}

void	allocate_cmd_node(t_data *data)
{
	t_cmd	*head;
	t_cmd	*node;
	int		i;
	int		len;

	i = 1;
	len = count_cmd(data) + 1;
	head = malloc(sizeof(t_cmd));
	if (!head)
		error_malloc();
	init_cmd_node(head);
	data->v_cmd = head;
	while (i < len)
	{
		node = malloc(sizeof(t_cmd));
		if (!node)
			error_malloc();
		init_cmd_node(node);
		head->next = node;
		head = node;
		i++;
	}
}
