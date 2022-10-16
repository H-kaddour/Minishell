/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_collector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 04:51:31 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/16 10:09:21 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_node_p_die(t_data *data, void *addr)
{
	d_free	*head;

	head = data->p_die;
	if (!head)
		return ;
	while (head->next)
		head = head->next;
	head->next = ft_calloc(1, sizeof(d_free));
	head->next->value = addr;
}

void	add_node_p_running(t_data *data, void *addr)
{
	r_free	*head;

	head = data->p_running;
	if (!head)
		return ;
	while (head->next)
		head = head->next;
	head->next = ft_calloc(1, sizeof(r_free));
	head->next->value = addr;
}

//t_free	*free_add_node(void)
//{
//	t_free	*head;
//
//	head = malloc(sizeof(t_free));
//	if (!head)
//		error_alloc();
//	head->value = 0;
//	head->next = 0;
//	return (head);
//}
//
//void	free_implementation(t_data *data, void *addr)
//{
//	t_free	*head;
//	t_free	*node;
//
//	head = data->free_ptr;
//	node = free_add_node();
//	node->value = addr;
//	while (head->next)
//		head = head->next;
//	head->next = node;
//}

//void	free_data_running_process(t_data *data)
//{
//	t_free	*node;
//
//	if (data->free_ptr->next)
//		node = data->free_ptr->next;
//	else
//		return ;
//	while (node)
//	{
//		free(node->value);
//		free(node);
//		node = node->next;
//	}
//	data->free_ptr->next = 0;
//}

//void	free_data_die_process(t_data *data)
//{
//	t_env	*env;
//
//	env = data->l_env;
//	while (env)
//	{
//		if (env->sec)
//			free(env->sec);
//		if (env->value)
//			free(env->value);
//		free(env);
//		env = env->next;
//	}
//	if (data->pwd_of_mysys)
//		free(data->pwd_of_mysys);
//}
